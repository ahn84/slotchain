# slotchain Roadmap

This document outlines the planned evolution of slotchain across future major and minor versions.

---

## 🎯 v0.2 — Stabilization & Polish

**Focus:** Finalize v0.1 foundation and improve developer experience

### Goals

| Category | Items |
|----------|-------|
| **Examples** | Complete example coverage for all features |
| **Testing** | Comprehensive test suite with edge cases |
| **Documentation** | Polish README, add tutorials and API reference |
| **API Audit** | Review naming, consistency, and ergonomics |

### Deliverables

- ✅ `small_fn` optimization finalized
- ✅ Production-ready documentation
- ✅ Stable v0.2.0 release

### Timeline

**Target:** Q1 2026

---

## 🛡️ v0.3 — Control & Safety

**Focus:** Enhanced connection management and optional thread safety

### Goals

| Feature | Description | Benefit |
|---------|-------------|---------|
| **Grouped Connections** | Connect multiple slots as a logical unit | Batch operations |
| **Bulk Disconnect** | Disconnect all connections by group/tag | Lifecycle management |
| **Thread-Safe Signal** | Optional `thread_safe_signal<T>` variant | Concurrent access |
| **Debug Diagnostics** | Connection tracking, leak detection | Development tools |

### Example

```cpp
signal<int> sig;
auto group = sig.connect_group({
    slot{[](int x) { /* ... */ }},
    slot{[](int x) { /* ... */ }}
});
group.disconnect_all(); // Disconnect entire group
```

### Timeline

**Target:** Q2 2026

---

## 🎨 v0.4 — Expressiveness

**Focus:** Advanced pipeline patterns and error handling

### Goals

| Feature | Description | Use Case |
|---------|-------------|----------|
| **`expected<T,E>` Pipelines** | Error-propagating slot chains | Robust error handling |
| **Short-Circuit Propagation** | Stop pipeline on condition | Early termination |
| **Signal Forwarding** | Signals emit to other signals | Event routing |
| **Zip / Combine Slots** | Multi-input transformations | Complex data flows |

### Example

```cpp
auto pipeline = slot{parse_int}           // expected<int, error>
              | slot{validate_range}       // expected<int, error>
              | slot{format_output};       // expected<string, error>

signal<string> input;
input.connect(pipeline);
```

### Timeline

**Target:** Q3 2026

---

## 🚀 v0.5+ — Async & Concurrency

**Focus:** Asynchronous execution and modern concurrency primitives

### Goals

| Feature | Description | Benefit |
|---------|-------------|---------|
| **Executor-Based Slots** | Slots execute on specified executors | Custom threading models |
| **`std::jthread` Integration** | Cooperative cancellation support | Modern C++20 threads |
| **Stop-Token Propagation** | Cancel in-flight slot execution | Graceful shutdown |

### Example

```cpp
executor_context ctx;

auto async_pipeline = slot{expensive_computation}.on(ctx.thread_pool());

signal<Data> sig;
sig.connect_async(async_pipeline);
sig(data); // Executes on thread pool
```

### Timeline

**Target:** Q4 2026 and beyond

---

## 🔮 Future Considerations (v1.0+)

Features under research and discussion:

- **Reactive Extensions** — Full Rx-style operators
- **Backpressure** — Flow control for high-throughput systems
- **Distributed Signals** — Network-aware event propagation
- **Metaprogramming Utilities** — Pipeline introspection and optimization

---

## 📊 Version Summary

| Version | Focus | Release |
|---------|-------|---------|
| **v0.1** | Core foundation | ✅ Released |
| **v0.2** | Stabilization | Q1 2026 |
| **v0.3** | Control & safety | Q2 2026 |
| **v0.4** | Expressiveness | Q3 2026 |
| **v0.5+** | Async & concurrency | Q4 2026+ |

---

## 🤝 Contributing to the Roadmap

Have ideas for future features? 

- **Open a Discussion** on GitHub to propose new capabilities
- **Check [AGENTS.md](../AGENTS.md)** for contribution guidelines
- **Review [DESIGN.md](DESIGN.md)** to ensure alignment with principles

All roadmap items are open to community feedback and may be adjusted based on user needs and technical discoveries.
