# CryptBaseBypass

The project creates a dynamic linked library that proxies the original `CryptBase.dll` and manually loads the `BCrypt.dll`. After that
the original `BCryptVerifySignature` method can be hooked, allowing us to bypass the check.

Having the proxy `CryptBase.dll` in the root directory is often enough for using the bypass (e.g. for **Frostbite games**).

Build in `Debug` mode to enable a console window for more verbose logs for whats currently happening.

The default output folder is called `Artifacts`.

# MinHook

The library [MinHook](https://github.com/TsudaKageyu/minhook) is used for hooking the function.

# License

This project is licensed under the [Apache License 2.0](LICENSE).