static const char TAB = '\t';

static char look; // Lookahead Character

#include <stdio.h> /* getchar, printf */
#include <stdlib.h> /* exit */
#include <string.h> /* strcat */
#include <ctype.h> /* isalpha */

static void GetChar()
{
    look = getchar();
}

static void Error(const char *source)
{
    puts("");
    printf("Error: %s.\n", source);
}

static void Abort(const char *source)
{
    Error(source);
    exit(1);
}

static char* SimpleCat(const char *first, const char *second, int clear)
{
    /* A slow, but ergonomically simple, way to cat two strings 
     * Do not use for large strings or multithreaded access */
    static char combined[1024];
    if(clear) {
        memset(combined, 0, sizeof(combined));
    }
    strcpy(combined, first);
    strcat(combined, second);
    return combined;
}

static char* SimpleString(char x)
{
    /* Do not use multi threaded */
    static char string[2];
    string[0] = x;
    return string;
}

static void Expected(const char *source)
{
    Abort(SimpleCat(source, "Expected", 1));
}

static void Match(char x)
{
    if(look == x) {
        GetChar();
    } else {
        Expected(SimpleString(x));
    }
}

static int IsAlpha(char c)
{
    return isalpha(c);
}

static int IsDigit(char c)
{
    return isdigit(c);
}

static char GetName()
{
    if(!IsAlpha(look)) {
        Expected("Name");
    }
    const char result = look;
    GetChar();
    return toupper(result);
}

static char GetNum()
{
    if(!IsDigit(look)) {
        Expected("Integer");
    }
    const char result = look;
    GetChar();
    return result;
}

static void Emit(const char *s)
{
    printf("\t%s", s);
}

static void EmitLn(const char *s)
{
    Emit(s);
    puts("");
}

static void Init()
{
    GetChar();
}

static void Expression()
{
    EmitLn(
        SimpleCat(
            SimpleCat("MOVE #", SimpleString(GetNum()), 1)
            , ",D0", 0
        )
    );
}

int main(void)
{
    Init();
    Expression();
}
