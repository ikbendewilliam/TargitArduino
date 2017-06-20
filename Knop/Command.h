// A class to check commands from a string
class Command
{
  private:
    String _value; // The command to search for

  public:
    Command(const String value) // The constructor needs the command to search for
    {
      _value = value; // Saves the command
    }

    bool inString(const String string) const // Check the given string for the command
    {
      return string.indexOf(_value) >= 0; // Return whether the command is found
    }

    int getFirstParameter(const String string) const // Get the first parameter from the command
    {
      int commandPlace = string.indexOf(_value); // find the command
      int braceOpen = string.indexOf('(', commandPlace + 1); // Get the index of (
      int braceClose = string.indexOf(')', braceOpen + 1); // Get the index of )
      String parameter = string.substring(braceOpen + 1, braceClose); // Get the string inbetween
      //Serial.println(parameter);
      return parameter.toInt(); // Transform the string inbetween to an int
    }
};
