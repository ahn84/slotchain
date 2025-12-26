# AGENTS.md — slotchain

This document defines **how AI agents (and humans) should work with this repository**.
It records architectural decisions, frozen APIs, constraints, and the intended direction of development.

⚠️ **This file is authoritative.**
If something is not written here, assume it must not be changed without explicit discussion.

---

## 1. Project Identity

**Project name:** slotchain  
**Language:** C++20  
**Distribution:** Header-only  
**Current version:** v0.1 (API frozen)

slotchain is a modern C++20 signal–slot library that combines:

- Compile-time static pipelines (zero-cost abstractions)
- Runtime dynamically composed pipelines
- Hybrid pipelines (static subgraphs inside runtime chains)
- Explicit lifetime management via disconnect tokens

---

## 2. Core Design Philosophy (Do NOT Violate)

Agents must preserve these principles:

1. **Zero-cost static pipelines**
   - Static pipelines must inline fully
   - No heap allocation on static fast path
2. **Explicit trade-offs**
   - Runtime flexibility costs runtime checks
   - No hidden magic
3. **No macros**
4. **No code generation**
5. **Header-only**
6. **Explicit lifetime management**
7. **No implicit thread safety**

If a change violates one of these, it is **out of scope**.

---

## 3. Architecture Overview

```
signal<T>
├── static connections (fast path)
│ └── small_fn<void(T)> → static pipeline
│
└── runtime pipelines
└── runtime_slot → runtime_slot → ...
```

### Layers
- **Static layer:** compile-time, type-safe, inlined
- **Runtime layer:** dynamic, type-erased, checked via `typeid`
- **Hybrid layer:** static pipeline wrapped as a runtime node

---

## 4. Static Pipeline Model (Frozen)

### Key types (public, frozen)
- `slot<In, Out, F>`
- `pipeline<F, G>`
- `operator|`

### Rules
- Type compatibility enforced at compile time
- Invalid chains must fail compilation
- No runtime branching inside static pipelines

Agents must NOT:
- Change slot or pipeline semantics
- Add dynamic behavior to static pipelines
- Add heap allocation here

---

## 5. Runtime Pipeline Model (Frozen Semantics)

### Key types
- `runtime_slot` (type-erased interface)
- `runtime_slot_impl`
- `runtime_slot_static`
- `runtime_pipeline`

### Rules
- Slots are added dynamically
- Compatibility is checked at runtime using `typeid`
- Incompatible chains throw `std::logic_error`
- Execution is linear and predictable

Agents must NOT:
- Remove runtime type checking
- Introduce silent failures
- Change exception behavior

---

## 6. Hybrid Model (Important)

Static pipelines may be embedded inside runtime pipelines:

```cpp
runtime_pipeline rp;
rp.add_static<int, int>(static_pipeline);


