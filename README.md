# C++ Password Manager

A tiny, local-first password manager built in C++.
Step 1 is a plaintext prototype for learning and testing.
Step 2 (coming next) swaps in real encryption (Argon2id + AEAD) without changing the CLI.

## Why this project?
- Demonstrates C++ fundamentals: file I/O, clean architecture, CLI, testing strategy.
- Evolves into a realistic security app with KDF + authenticated encryption.
- Portfolio-ready: readable code, clear docs, and CI.

## Features (Step 1)
- 'pm init': create an empty vault file ('vault.dev')
- 'pm add': add service/username/password/notes (plaintext for now)
- 'pm list': list all services
- 'pm show <service>': display entry of chosen service

> Security note: Step 1 stores plaintext. Do **not** use real information.
> Step 2 will introduce **Argon2id** (KDF) and **AEAD** (ChaCha20-Poly1305 or AES-GCM).

## Build
```bash
cmake -S . -B build
cmake --build build
```
## Roadmap

**Phase 1 - Prototype (current)**
- [x] CLI: 'init', 'add', 'list', 'show'
- [x] Plaintext file store

**Phase 2 - Local Security**
- [ ] Master password prompt on unlock
- [ ] Key derivation with Argon2id (libsodium)
- [ ] AEAD encryption (ChaCha20-Poly1305 or AES-GCM)
- [ ] Atomic writes for encrypted file (already in plaintext version)
- [ ] Auto-lock timer (forget key after N minutes)

**Phase 3 - Usability**
- [ ] Password generator (length, charset, symbols toggles)
- [ ] Strength meter (entropy estimate)
- [ ] 'update' and 'remove' commands
- [ ] 'find <query>' (substring search on service)
- [ ] Clipboard copy with timed clear ('--copy')

**Phase 4 - Interop & Backups**
- [ ] CSV import (immediately encrypted at rest)
- [ ] Encrypted backup/restore
- [ ] Config for default vault location (~/.passman/vault)

**Phase 5 - Nice-to-haves**
- [ ] Unit tests (Vault, File store, CLI)
- [ ] Fuzz tests for parser
- [ ] Optional Qt GUI reusing core library
- [ ] GitHub Releases & demo GIFs in README