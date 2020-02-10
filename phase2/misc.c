// misc.c, 159

add 2 new functions:

// assume: str is NUL-delimited, and has >0 byte space left
void-returning StrAdd with 2 input: a character and a char * (string)
   we want to append the new character at the end of the string
   so we first need to find the end of the string by advancing
   the string pointer until it point to a NUL, and that's where
   the new character is added, and next to the new character is
   a new NUL to keep the string NUL-delimited.

// assume: source string is properly NUL-delimited, destination is
// large enough in space to perform the copying
void-returning StrCpy with 2 inputs: both char *, as the source
and destination of the copy
make sure the destination copy will also be NUL-delimited

