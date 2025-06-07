# FreeSteamCodeGenerator

## About This Project

This is a recreation of a C++ troll console application I originally wrote years ago, called **Free Steam Code Generator**. The program pretends to generate Steam gift codes, ultimately reveals its troll nature, and flashes colorful messages in the console.

## The Story: Lost & Found

### Losing the Source

Years ago, I created this program as a joke, but over time, I lost all the original project and source files. All that remained was the compiled `.exe` binary.

### Recovery from Disassembly

Recently, I was able to disassemble the binary using **IDA Free**, revealing the embedded strings and general program logic, but not the precise C++ code or structure. With only the disassembly and some hazy memories of how the program worked, I set out to recover my project.

### Rebuilding with AI

To truly restore the program, I worked with GitHub Copilot and other AI tools to:

- Analyze the disassembly output and reconstruct the likely logic and code structure.
- Fill in missing details from my memory (such as the animated color-flashing troll sequence).
- Modernize the code, making it readable, maintainable, and cross-platform.

### Improvements & Modernization

- **Cross-platform**: The new version runs on both Windows and Linux/macOS terminals.
- **Color Flashing**: Improved color flashing using native Windows console commands and ANSI escape codes on Linux/macOS.
- **Cleaner Code**: Modern C++11 code, with threading and signal handling for smooth user experience.
- **Customizable Build**: Simple build script included.

## Building

On Linux/macOS:

```sh
./build.sh
```

On Windows (MinGW or similar):

```sh
g++ -std=c++11 -o FreeSteamCodeGenerator FreeSteamGenerator.cpp -pthread
```

## Running

Launch the built executable:

```sh
./FreeSteamCodeGenerator
```
or (on Windows)
```sh
FreeSteamCodeGenerator.exe
```

## How It Works

1. Shows a fake Steam code generator banner.
2. Prompts for "start".
3. Pretends to generate a code, then displays a fake code.
4. Flashes the troll messages in wild colors, infinitely, until the user exits.

## Credits

- **Disassembly**: [IDA Free](https://hex-rays.com/ida-free/)
- **Rebuild & AI Assistance**: GitHub Copilot and ChatGPT, guided by my own memories of the original troll program.

---

**If you lost your source, don't give up!** With a little disassembly and some help from modern AI, you can revive even the weirdest projects from the past.
