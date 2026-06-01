# Contributing to Hospital Management System

Thank you for your interest in contributing! We welcome contributions from everyone. This document provides guidelines and instructions for contributing.

## 🎯 How to Contribute

### 1. **Report Bugs**
- Check if the bug has already been reported in [Issues](https://github.com/Talha925-hub/Hospital-Management-System-in-C-/issues)
- If not, create a new issue with:
  - Clear title and description
  - Steps to reproduce
  - Expected vs actual behavior
  - Environment details (OS, compiler, SFML version)

### 2. **Suggest Enhancements**
- Open an issue with the label `enhancement`
- Describe the feature and why it would be useful
- Provide examples or mockups if applicable

### 3. **Code Contributions**
Follow these steps:

#### Fork and Clone
```bash
git clone https://github.com/YOUR-USERNAME/Hospital-Management-System-in-C-.git
cd Hospital-Management-System-in-C-
```

#### Create a Branch
```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/bug-fix-name
```

#### Make Changes
- Write clean, well-commented code
- Follow C++ best practices
- Test your changes thoroughly
- Keep commits atomic and descriptive

#### Commit and Push
```bash
git commit -m "Add: Brief description of changes"
git push origin feature/your-feature-name
```

#### Create a Pull Request
- Go to the repository and click "New Pull Request"
- Provide a clear description of your changes
- Link to related issues (if any)
- Wait for code review

## 📋 Code Style Guidelines

### C++ Standards
- Use **C++11 or higher**
- Follow **Google C++ Style Guide** conventions
- Use meaningful variable names
- Add comments for complex logic
- Keep functions focused and small

### SFML Best Practices
- Properly manage window resources
- Handle events correctly
- Use appropriate event types
- Clear graphics objects when done

### Class Structure
```
class ClassName {
private:
    // Member variables
    int id;
    string name;

public:
    // Constructors and destructors
    ClassName();
    ~ClassName();

    // Public methods
    void displayInfo();
    bool addRecord();
};
```

## 🧪 Testing

Before submitting:
- Compile without warnings: `g++ -Wall -Wextra`
- Test all CRUD operations
- Test role-based access
- Verify file operations
- Test edge cases

## 📝 Commit Message Format

```
Type: Brief description (50 chars max)

Detailed explanation if needed (wrap at 72 chars)
- Use bullet points for multiple changes
- Reference issues with #123

Type options:
- Add: New feature
- Fix: Bug fix
- Improve: Code improvement
- Docs: Documentation update
- Refactor: Code restructuring
```

## ✅ Pull Request Checklist

- [ ] Code follows style guidelines
- [ ] Comments added for new code
- [ ] Documentation updated
- [ ] No new warnings generated
- [ ] Feature/fix tested locally
- [ ] Commit messages are clear
- [ ] No hardcoded paths or credentials

## 🤝 Community Guidelines

- Be respectful and inclusive
- Provide constructive feedback
- Help others when possible
- Avoid spamming or self-promotion
- Give credit where due

## 💡 Areas for Contribution

- Database integration
- Enhanced UI/UX
- Additional modules
- Performance optimization
- Documentation improvements
- Bug fixes
- Test coverage

## 📞 Questions?

- Check existing issues and discussions
- Comment on related issues
- Open a discussion for questions

## 📄 License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

**Thank you for making this project better!** 🎉