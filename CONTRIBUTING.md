# Contributing to slotchain

Thank you for your interest in contributing to **slotchain**! We appreciate your time and effort in helping improve this library.

---

## 📋 Project Status

**Current Version:** v0.1 (API Frozen)

⚠️ **Important:** Breaking changes are **not accepted** until v0.2. All v0.1.x contributions must maintain backward compatibility.

---

## 🎯 Core Contribution Rules

All contributions must adhere to these fundamental principles:

| Rule | Description |
|------|-------------|
| **Header-Only** | No compiled libraries or source files |
| **No Macros** | Pure C++ templates, no preprocessor magic |
| **C++20 Only** | Modern C++ features required |
| **Explicit Design** | No hidden threading, scheduling, or side effects |

---

## 🔧 Types of Contributions

### ✅ Accepted in v0.1.x

The following contributions are welcome for the current stable release:

- **Bug Fixes** — Resolve issues without changing public APIs
- **Documentation** — Improve clarity, add examples, fix typos
- **Tests & Examples** — Expand test coverage and usage demonstrations
- **Performance Optimizations** — Improve efficiency without semantic changes

### 🚧 Deferred to v0.2+

These contributions will be considered for future releases:

- **New Features** — Additional functionality beyond current scope
- **Thread-Safe Variants** — Concurrent signal/slot implementations
- **Async Support** — Asynchronous execution models

---

## ✔️ Pull Request Checklist

Before submitting your PR, ensure:

- [ ] **No Public API Break** — All existing code continues to work
- [ ] **Tests Added/Updated** — Changes are covered by tests
- [ ] **Documentation Updated** — User-facing docs reflect changes
- [ ] **Design Rationale Explained** — PR description justifies approach

---

## 📝 Code Style Guidelines

### Philosophy

- **Clarity over Cleverness** — Readable code is maintainable code
- **Minimal Templates** — Avoid template metaprogramming unless necessary
- **User-Friendly Errors** — Keep compiler error messages readable

### Formatting

- Use consistent indentation (spaces preferred)
- Follow existing code patterns in the repository
- Keep line length reasonable (≤100 characters recommended)

---

## 🔍 Review Process

All pull requests are reviewed for alignment with:

1. **[DESIGN.md](docs/DESIGN.md)** — Architectural principles and patterns
2. **[AGENTS.md](AGENTS.md)** — AI agent and contributor guidelines

Reviews typically take 2-7 days. We'll provide constructive feedback to help your contribution succeed.

---

## 🤝 Getting Help

- **Questions?** Open a GitHub Discussion
- **Bug Reports?** Create an Issue with minimal reproduction
- **Feature Ideas?** Propose in Discussions before implementing

Thank you for contributing to slotchain! 🚀
