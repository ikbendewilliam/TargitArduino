// All classes in a separate header file (with the same name)
// Classname starts with a capital letter
class Command
{
    // First defie private values
    // Each value on a new line
    // value start with underscore _ and then a lowercase letter
    // Initialize in statement, unless it is set in the constructor
  private:
    String _value;

  public:
    Command(const String value)
    {
      _value = value;
    }

    bool inString(const String string) const
    {
      return string.indexOf(_value) >= 0;
    }
};

