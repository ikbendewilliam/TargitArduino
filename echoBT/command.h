class Command
{
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

