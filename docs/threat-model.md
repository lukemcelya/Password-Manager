# Threat Model

## Assets
- Password entries: service, username, password, notes
- Master password (Phase 2+)
- Encrypted vault file

## Adversaries
- **Opportunistic attacker** who gets a copy of your vault file (e.g., via stolen laptop or backup)
- **Curious local user** on the same machine/account

## Out of Scope
- Malware/OS compromise (keyloggers, screen capture, memory scraping)
- Cloud sync and remote storage
- Physical attaccks while the app is unlocked
- Side-channel attacks

## Current Status (Phase 1: Prototype)
- Plaintext storage for learning and end-to-end wiring
- DO NOT store real information

## Planned Defenses (Phase 2+)
- **Key Derivation:** Argon2id with memory hardness (tuned for ~300ms on dev box)
- **Authenticated Encryption:** ChaCha20-Poly1305 (or AES-256-GCM) for confidentiality + integrity
- **Key Handling:** Cache key in memory for a short time; zero sensitive buffers after use
- **Auto-Lock:** Timer-based lock to release key from memory after inactivity
- **File Safety:** Atomic writes to avoid partial/corrupted vault files

## Residual Risks (Even After Phase 2)
- If the OS is compromised (malware), passwords can be captured when unlocked
- Shoulder surfing and weak master passwords
- Backups: if copied while unlocked or from memory dumps