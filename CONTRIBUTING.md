# Contributing to Ethical Hacking Learning Repository

Thank you for your interest in contributing! This repository aims to help people learn ethical hacking responsibly.

## How to Contribute

### Types of Contributions

1. **New Projects**: Add new educational projects to existing levels
2. **Improvements**: Enhance existing code or documentation
3. **Bug Fixes**: Fix errors in code or documentation
4. **Additional Resources**: Add helpful links and references
5. **Translations**: Help translate materials to other languages

### Guidelines

#### Code Contributions

1. **Educational Focus**: All code should be clear and well-commented for learning
2. **Security**: Include both vulnerable and secure versions when demonstrating concepts
3. **Portability**: Code should work on Linux systems (Ubuntu/Debian preferred)
4. **Documentation**: Each project must have a comprehensive README

#### Code Style

**C Code:**
- Use meaningful variable names
- Comment complex sections
- Include compilation instructions
- Provide example usage

**Assembly Code:**
- Use Intel syntax
- Comment every section
- Explain what each instruction does
- Include assembly and linking instructions

**Python Code:**
- Follow PEP 8
- Include docstrings
- Type hints when appropriate
- Python 3.6+ compatible

#### Project Structure

Each new project should follow this structure:
```
project-name/
├── README.md           # Detailed documentation
├── Makefile           # Build instructions
├── src/               # Source files
├── examples/          # Example usage
└── exercises/         # Practice exercises
```

#### Documentation

All README files should include:
- Overview of concepts
- Learning objectives
- Prerequisites
- Step-by-step instructions
- Common pitfalls
- Additional resources

### Ethical Guidelines

⚠️ **Critical Requirements**

All contributions MUST:
1. Include legal disclaimers
2. Emphasize ethical use
3. Warn against unauthorized testing
4. Provide only educational content
5. Not include actual exploits for real systems
6. Not include stolen data or credentials

### Pull Request Process

1. **Fork the repository**
   ```bash
   git clone https://github.com/alektebel/ethical-hacking.git
   cd ethical-hacking
   git checkout -b feature/your-feature-name
   ```

2. **Make your changes**
   - Follow the guidelines above
   - Test your code thoroughly
   - Update documentation

3. **Commit your changes**
   ```bash
   git add .
   git commit -m "Add: Brief description of your changes"
   ```

4. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```

5. **Submit a Pull Request**
   - Clear title describing the change
   - Detailed description of what and why
   - Reference any related issues
   - Include test results

### Review Process

- PRs will be reviewed for:
  - Educational value
  - Code quality
  - Documentation completeness
  - Ethical compliance
  - Technical accuracy

- Reviewers may request changes
- Be responsive to feedback
- All discussions should be respectful

### Testing

Before submitting:

1. **Compile all C code**: Ensure no errors (warnings are okay if educational)
2. **Run all programs**: Verify they work as expected
3. **Test on clean system**: Use a VM to test installation instructions
4. **Check documentation**: Read through all READMEs for clarity

### Adding New Levels or Topics

If you want to add a completely new level or major topic:

1. Open an issue first to discuss
2. Explain the educational value
3. Provide an outline
4. Wait for approval before starting work

### Code of Conduct

- Be respectful and professional
- Focus on education and learning
- No offensive language or content
- Help others learn
- Report concerning content

### Questions?

- Open an issue for questions about contributing
- Tag with "question" label
- Be specific about what you need help with

### Recognition

Contributors will be:
- Listed in project documentation
- Credited in commit history
- Mentioned in release notes (for significant contributions)

## Legal Reminder

By contributing, you agree that:
- Your contributions will be licensed under the MIT License
- Your code is your own or properly licensed
- You understand the ethical implications
- You will not contribute malicious code

Thank you for helping make security education accessible and responsible!
