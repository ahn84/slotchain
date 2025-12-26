# slotchain — Design Document

## 📖 Overview

**slotchain** is a modern, header-only C++20 signal–slot library that provides:

- ⚡ **Compile-time static pipelines** — Zero runtime cost
- 🔄 **Runtime dynamically composed pipelines** — Maximum flexibility
- 🔗 **Hybrid pipelines** — Static subgraphs embedded in runtime chains
- 🎯 **Explicit lifetime control** — Via disconnect tokens and RAII

The library prioritizes **correctness**, **explicit trade-offs**, and **zero-cost abstractions**.

---

## 🎯 Core Principles

These principles guide every design decision:

| # | Principle | Meaning |
|---|-----------|---------|
| 1 | **Zero Runtime Cost** | Static pipelines compile to direct function calls |
| 2 | **Explicit Runtime Cost** | Dynamic features clearly marked and opt-in |
| 3 | **No Magic** | No macros, no code generation, pure C++ |
| 4 | **Header-Only** | Template-based, no compiled libraries |
| 5 | **Explicit Lifetime** | Clear ownership, manual disconnect control |
| 6 | **No Hidden Behavior** | No threading, scheduling, or side effects |

---

## 🏗️ Architecture Overview

```
signal<T>
├── Static Connections (Fast Path)
│   └── small_fn<void(T)> → Inlined Static Pipeline
│
└── Runtime Pipelines (Dynamic Path)
    └── runtime_slot → runtime_slot → runtime_slot → ...
```

### Execution Order

When a `signal<T>` emits a value:
1. **Static connections** execute first (fully inlined)
2. **Runtime pipelines** execute second (type-erased dispatch)

---

## ⚡ Static Pipeline Model

### Composition

Static pipelines are composed at compile time using:

- `slot<In, Out, F>` — Typed transformation node
- `pipeline<F, G>` — Composition of two nodes
- `operator|` — Fluent chaining syntax

### Example

```cpp
auto pipeline = slot{[](int x) { return x * 2; }}
              | slot{[](int x) { return x + 1; }};

signal<int> sig;
sig.connect(pipeline);
sig(5); // Executes (5 * 2) + 1 = 11
```

### Properties

| Property | Benefit |
|----------|---------|
| **Compile-Time Type Safety** | Errors caught at compile time |
| **Fully Inlined** | Zero function call overhead |
| **No Virtual Dispatch** | Direct execution |
| **No Heap Allocation** | Stack-based or register-only |

### Use Cases

- Performance-critical event handlers
- Known pipeline structure at compile time
- When type transformations are static

---

## 🔄 Runtime Pipeline Model

### Components

Runtime pipelines are built from:

- `runtime_slot` — Type-erased transformation node
- `runtime_pipeline` — Container for dynamic slot chains

### Example

```cpp
runtime_pipeline pipeline;
pipeline.add_slot(runtime_slot::create<int, int>([](int x) { return x * 2; }));
pipeline.add_slot(runtime_slot::create<int, std::string>([](int x) { 
    return "Result: " + std::to_string(x); 
}));

signal<int> sig;
sig.connect_runtime(pipeline);
sig(5); // Outputs "Result: 10"
```

### Properties

| Property | Characteristic |
|----------|----------------|
| **Dynamic Composition** | Slots added/removed at runtime |
| **Runtime Type Checks** | Compatibility verified via `typeid` |
| **Stable Storage** | Intermediate results stored between slots |
| **Virtual Dispatch** | Small overhead per slot invocation |

### Use Cases

- Plugin systems with unknown slots
- Configurable processing pipelines
- User-defined transformation chains

---

## 🔗 Hybrid Model

### Concept

Static pipelines can be **embedded** into runtime pipelines as a single node.

### Benefits

| Benefit | Description |
|---------|-------------|
| **Runtime Flexibility** | Dynamic slot ordering |
| **Static Performance** | Fast execution inside static chunks |
| **Reduced Dispatch** | One virtual call for entire static subgraph |

### Example

```cpp
auto static_chunk = slot{[](int x) { return x * 2; }}
                  | slot{[](int x) { return x + 1; }};

runtime_pipeline pipeline;
pipeline.add_slot(runtime_slot::from_static(static_chunk));
pipeline.add_slot(runtime_slot::create<int, int>([](int x) { return x * 10; }));

signal<int> sig;
sig.connect_runtime(pipeline);
sig(5); // ((5 * 2) + 1) * 10 = 110
```

---

## 📡 Signal Model

### Responsibilities

`signal<T>` serves as:

- **Connection Manager** — Owns all connections
- **Event Dispatcher** — Broadcasts values to slots
- **Lifetime Coordinator** — Manages disconnect tokens

### Emit Order

```
1. Execute all static connections (fast path)
2. Execute all runtime pipelines (dynamic path)
```

### Example

```cpp
signal<int> sig;

// Static connection
sig.connect(slot{[](int x) { std::cout << "Static: " << x << "\n"; }});

// Runtime connection
runtime_pipeline rt;
rt.add_slot(runtime_slot::create<int, void>([](int x) { 
    std::cout << "Runtime: " << x << "\n"; 
}));
sig.connect_runtime(rt);

sig(42);
// Output:
// Static: 42
// Runtime: 42
```

---

## 🔌 Lifetime Management

### Components

| Type | Purpose | Usage |
|------|---------|-------|
| `connection_node` | Tracks liveness | Internal shared state |
| `connection` | Manual disconnect | `conn.disconnect()` |
| `scoped_connection` | RAII semantics | Auto-disconnect on scope exit |

### Disconnect Behavior

- Disconnected connections are **skipped**, not erased
- This avoids iterator invalidation during emit
- Future optimizations may prune dead nodes

### Example

```cpp
signal<int> sig;
auto conn = sig.connect(slot{[](int x) { std::cout << x << "\n"; }});

sig(1); // Prints: 1
conn.disconnect();
sig(2); // (no output)
```

---

## 🧵 Threading Model

### Default Behavior

slotchain is **not thread-safe by default**.

### Rationale

- Preserves single-threaded performance
- Avoids hidden synchronization costs
- Gives users explicit control

### Thread Safety

Thread-safe variants are **opt-in** and planned for v0.3:

- `thread_safe_signal<T>`
- Mutex-protected connection lists
- Atomic disconnect operations

---

## 🚫 Non-Goals

These are explicitly **out of scope** for slotchain:

| Non-Goal | Reason |
|----------|--------|
| **Full Reactive Streams** | Specialized domain, other libraries exist |
| **GUI Object Lifetime** | Application-specific concern |
| **Implicit Async** | Requires executor integration (v0.5+) |
| **ABI Stability** | Header-only, template-based design |

---

## 📊 Performance Characteristics

| Operation | Static | Runtime |
|-----------|--------|---------|
| Connection | Compile-time | `O(1)` allocation |
| Emit | `O(1)` inline | `O(n)` dispatch |
| Type Check | Compile-time | Runtime `typeid` |
| Memory | Stack | Heap per slot |

---

## 💡 Usage Guidelines

### When to Use Static Pipelines

✅ Performance-critical paths  
✅ Known transformations at compile time  
✅ Type safety is paramount  

### When to Use Runtime Pipelines

✅ Plugin architectures  
✅ User-configurable processing  
✅ Dynamic slot composition  

### When to Use Hybrid Pipelines

✅ Balance between flexibility and performance  
✅ Static chunks with dynamic ordering  
✅ Optimize hot paths in dynamic systems  

---

## 🎓 Summary

slotchain demonstrates a **clean, modern C++20 approach** to signal–slot systems that:

- Scales from compile-time static pipelines to dynamic runtime graphs
- Makes trade-offs explicit and transparent
- Prioritizes correctness and zero-cost abstractions
- Empowers users with full control over performance and behavior

For implementation status, see [CURRENT_STATE.md](CURRENT_STATE.md).

For future enhancements, see [ROADMAP.md](ROADMAP.md).
