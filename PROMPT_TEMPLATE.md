# AI Agent Guidelines for slotchain

This document provides instructions for AI agents contributing to the **slotchain** C++20 header-only library.

---

## 🚀 Before Making Changes

Follow this workflow for every contribution:

1. **Read [AGENTS.md](AGENTS.md)** — This is the authoritative source of truth
2. **Confirm Target Version** — Is this for v0.1 (stable) or v0.2+ (future)?
3. **Classify Change Type** — Is this breaking or additive?

---

## 🔒 Mandatory Constraints

These constraints are **non-negotiable** and must be respected in all contributions:

| Constraint | Description |
|------------|-------------|
| **Header-Only** | No compiled libraries or `.cpp` files |
| **No Macros** | Pure template-based design only |
| **No Code Generation** | No external preprocessing or metaprogramming tools |
| **Explicit Concurrency** | No implicit thread safety — users must opt-in |
| **Zero-Cost Static Path** | Static pipelines must have no runtime overhead |

---

## 💡 Design Review Questions

When proposing any change, you **must** answer these questions:

### 1. Layer Impact
**Which architectural layer is affected?**
- Static pipelines
- Runtime pipelines
- Hybrid nodes
- Signal dispatch
- Lifetime management

### 2. Performance Analysis
**What is the performance impact?**
- Does this add runtime overhead?
- Are there additional allocations?
- How does this affect static pipeline optimization?

### 3. Lifetime Implications
**What are the object lifetime implications?**
- Who owns what?
- Are there dangling reference risks?
- Do users need new lifetime management tools?

### 4. Compatibility Assessment
**Is this backward compatible?**
- Does existing code still compile?
- Are there any behavioral changes to existing APIs?
- Can users migrate incrementally?

---

## 🎨 Contribution Philosophy

### Design Before Implementation

When in doubt:
- **Propose design first, not code**
- Discuss trade-offs and alternatives
- Get feedback before implementing

### Clarity Over Cleverness

- Prefer readable, maintainable solutions
- Avoid unnecessary template complexity
- Keep error messages user-friendly

---

## 📚 Key Resources

- **[AGENTS.md](AGENTS.md)** — Authoritative guidelines
- **[DESIGN.md](docs/DESIGN.md)** — Architecture and principles
- **[CONTRIBUTING.md](CONTRIBUTING.md)** — Contribution process

---

**Remember:** slotchain prioritizes correctness, explicit trade-offs, and zero-cost abstractions. Every decision should align with these core values.
