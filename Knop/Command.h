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

    int getFirstParameter(const String string) const
    {
      int commandPlace = string.indexOf(_value);
      int braceOpen = string.indexOf('(', commandPlace + 1);
      int braceClose = string.indexOf(')', braceOpen + 1);
      String parameter = string.substring(braceOpen + 1,braceClose);
      //Serial.println(parameter);
      return parameter.toInt();
    }
};
