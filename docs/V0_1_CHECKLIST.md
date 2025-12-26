# slotchain v0.1 Release Checklist

This checklist tracks the completion status of all tasks required for the v0.1.0 release.

---

## 🎯 Code Implementation

Core functionality required for v0.1 release:

| Feature | Status | Notes |
|---------|--------|-------|
| Static pipelines | ✅ Complete | Compile-time composition with zero overhead |
| Runtime pipelines | ✅ Complete | Dynamic slot composition with type erasure |
| Hybrid pipelines | ✅ Complete | Static chunks in runtime chains |
| Disconnect tokens | ✅ Complete | Manual lifetime management via `connection` |
| `scoped_connection` | ✅ Complete | RAII-based automatic disconnect |
| Finalize `small_fn.hpp` | ⏳ In Progress | Small function optimization wrapper |

---

## 🏗️ Build System

CMake configuration and integration:

| Task | Status | Description |
|------|--------|-------------|
| Header-only structure | ✅ Complete | No compiled libraries required |
| CMake INTERFACE target | ✅ Complete | Easy `target_link_libraries` integration |
| C++20 enforcement | ✅ Complete | Compiler version checks in place |

### Build Instructions

```bash
mkdir build && cd build
cmake ..
cmake --build .
ctest  # Run tests
```

---

## 📚 Documentation

User-facing and developer documentation:

| Document | Status | Purpose |
|----------|--------|---------|
| Design document | ✅ Complete | Architecture and principles |
| Current state | ✅ Complete | Feature inventory |
| Roadmap | ✅ Complete | Future version planning |
| README polish | ⏳ Pending | Main entry point for users |

### Documentation Locations

- **Design:** [docs/DESIGN.md](DESIGN.md)
- **Current State:** [docs/CURRENT_STATE.md](CURRENT_STATE.md)
- **Roadmap:** [docs/ROADMAP.md](ROADMAP.md)
- **Contributing:** [CONTRIBUTING.md](../CONTRIBUTING.md)

---

## ✅ Quality Assurance

Testing and validation:

| Task | Status | Details |
|------|--------|---------|
| Examples compile | ✅ Verified | All 4 examples build successfully |
| Tests pass | ✅ Verified | All unit tests passing |
| CI setup | 🔲 Optional | GitHub Actions (deferred) |

### Test Coverage

- ✅ Static pipeline composition
- ✅ Runtime pipeline dynamics
- ✅ Disconnect semantics
- ✅ Type safety validation

### Example Programs

- [examples/static_pipeline.cpp](../examples/static_pipeline.cpp) — Basic static composition
- [examples/runtime_pipeline.cpp](../examples/runtime_pipeline.cpp) — Dynamic slot chains
- [examples/hybrid_pipeline.cpp](../examples/hybrid_pipeline.cpp) — Mixed static/runtime
- [examples/scoped_disconnect.cpp](../examples/scoped_disconnect.cpp) — RAII connection management

---

## 🚀 Release Tasks

Final steps before v0.1.0 goes live:

| Task | Status | Action |
|------|--------|--------|
| Tag v0.1.0 | 🔲 Pending | `git tag -a v0.1.0 -m "Initial stable release"` |
| GitHub release | 🔲 Pending | Create release notes and attach artifacts |

### Release Criteria

Before tagging v0.1.0, ensure:

- [ ] All ✅ Complete items verified
- [ ] ⏳ In Progress items resolved or documented
- [ ] README.md finalized
- [ ] No critical bugs outstanding
- [ ] API frozen and documented

---

## 📊 Progress Summary

**Overall Completion:** ~85%

**Remaining Work:**
- Finalize `small_fn.hpp` optimization
- Polish README.md
- Create GitHub release

**Estimated Release:** Q1 2026

---

## 🤝 How to Help

Contributors can assist with:

1. **Testing** — Run examples and tests on different platforms
2. **Documentation** — Review and improve README clarity
3. **Feedback** — Report any API ergonomics issues

See [CONTRIBUTING.md](../CONTRIBUTING.md) for guidelines.
