# Current State — slotchain v0.1

This document provides a snapshot of what **has been implemented** and what **remains outside the scope** of the current release.

---

## ✅ Implemented Features

The following capabilities are fully implemented and stable in v0.1:

### Core Pipeline Types

| Feature | Description | Status |
|---------|-------------|--------|
| **Static Compile-Time Pipelines** | Fully inlined, zero-cost pipelines composed at compile time | ✅ Complete |
| **Runtime Dynamic Pipelines** | Type-erased slots connected at runtime with dynamic dispatch | ✅ Complete |
| **Hybrid Static/Runtime Nodes** | Static pipelines embedded as single nodes in runtime chains | ✅ Complete |

### Performance & Design

| Feature | Description | Status |
|---------|-------------|--------|
| **Zero-Cost Static Path** | Static pipelines have no runtime overhead | ✅ Guaranteed |
| **Header-Only** | No compilation units, template-based only | ✅ Complete |
| **C++20** | Modern C++ features (concepts, requires, etc.) | ✅ Required |

### Connection Management

| Feature | Description | Status |
|---------|-------------|--------|
| **Disconnect Tokens** | Manual connection lifetime control via `connection` | ✅ Complete |
| **RAII Scoped Connections** | Automatic disconnect with `scoped_connection` | ✅ Complete |

### Build System

| Feature | Description | Status |
|---------|-------------|--------|
| **CMake INTERFACE Target** | Easy integration via `target_link_libraries` | ✅ Complete |

---

## ❌ Explicitly Not Implemented

These features are **intentionally excluded** from v0.1 to maintain focus and simplicity:

### Concurrency

| Feature | Reason for Exclusion |
|---------|---------------------|
| **Thread Safety** | No implicit locks — users must opt into thread-safe wrappers |
| **Async Execution** | Requires executor model (planned for v0.5+) |

### Advanced Pipeline Features

| Feature | Reason for Exclusion |
|---------|---------------------|
| **Error-Propagating Pipelines** | Requires `expected<T,E>` integration (planned for v0.4) |
| **Multi-Input Slots** | Zip/combine operators deferred to v0.4 |

### Automatic Optimization

| Feature | Reason for Exclusion |
|---------|---------------------|
| **Automatic Pruning** | Disconnected nodes remain in list — manual cleanup required |

---

## 🔒 API Stability Guarantee

### What's Frozen

All **public APIs** introduced in v0.1 are **frozen** and will not break in v0.1.x patch releases.

This includes:
- `signal<T>` interface
- `slot<In, Out, F>` composition
- `runtime_slot` and `runtime_pipeline`
- `connection` and `scoped_connection` types
- Operator overloads (`operator|`)

### What May Change

Internal implementation details may evolve, but:
- No breaking changes to public APIs
- Future changes will be **additive**, not breaking
- Semantic behavior remains consistent

---

## 🚀 Next Steps

For planned enhancements, see [ROADMAP.md](ROADMAP.md).

For current implementation progress, see [V0_1_CHECKLIST.md](V0_1_CHECKLIST.md).
