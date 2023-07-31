#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// checks if a valid register is accessed (by testing if op < 8)
// exits if op >= 8 as it makes the instruction illegal

void check_index(unsigned char op)
{
    if (op < 8)
    {
        return;
    }
    else
    {
        printf("Illegal instruction\n");
        exit(-1);
    }
}

unsigned char memory[256] = {
    0x00,0x00,0x80,0x00,0x01,0x00,0x00,0x02,0x1C,0x03,0x00,0x01,0x08,0x03,0x00,0x02,
    0x03,0x07,0x05,0x03,0x00,0x04,0x00,0x01,0x01,0x01,0x01,0x02,0x02,0x01,0x06,0x02,
    0x09,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x6d,0x73,0x68,0x6e,0x82,0x7a,0x37,0x66,0x7a,0x3a,0x6a,0x79,0x3a,0x7b,0x66,0x80,
    0x3a,0x7b,0x66,0x7a,0x37,0x66,0x6d,0x79,0x3a,0x3a,0x84,0x11,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char registers[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void printRegisters()
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if (registers[i] == 0x00)
        {
            printf("0x00, ");
        }
        else
        {

            printf("%c, ", registers[i]);

        }

    }

}

 

int valueOf(char symbol)

{

    switch (symbol)

    {

    case '0':

        return 0;

    case '1':

        return 1;

    case '2':

        return 2;

    case '3':

        return 3;

    case '4':

        return 4;

    case '5':

        return 5;

    case '6':

        return 6;

    case '7':

        return 7;

    case '8':

        return 8;

    case '9':

        return 9;

    case 'A':

    case 'a':

        return 10;

    case 'B':

    case 'b':

        return 11;

    case 'C':

    case 'c':

        return 12;

    case 'D':

    case 'd':

        return 13;

    case 'E':

    case 'e':

        return 14;

    case 'F':

    case 'f':

        return 15;

    default:

    {

        printf("Cannot decode that symbol: %c", symbol);

        return -1;

    }

    }

}

 

char *hexToAscii(char hex[])

{

    if (hex[0] == '0' && hex[1] == 'x')

    {

        hex[0] = hex[2];

        hex[1] = hex[3];

        hex[2] = '\0';

        hex[3] = '\0';

    }

 

    int hexLength = strlen(hex);

    char *text = NULL;

 

    if (hexLength > 0)

    {

        int symbolCount;

        int oddHexCount = hexLength % 2 == 1;

        if (oddHexCount)

            symbolCount = (hexLength / 2) + 1;

        else

            symbolCount = hexLength / 2;

 

        text = malloc(symbolCount + 1);

 

        int lastIndex = hexLength - 1;

        for (int i = lastIndex; i >= 0; --i)

        {

            if (((lastIndex - i) % 2 != 0))

            {

                int dec = 16 * valueOf(hex[i]) + valueOf(hex[i + 1]);

                if (oddHexCount)

                    text[i / 2 + 1] = dec;

                else

                    text[i / 2] = dec;

            }

            else if (i == 0)

            {

                int dec = valueOf(hex[0]);

                text[0] = dec;

            }

        }

        text[symbolCount] = '\n';

    }

    return text;

}

 

int main()

{

 

    if (registers[0] == 0x00)

    {

    }

   

 

    int instruction_pointer = 0;

    int i = 0;

    while (1==1)

    {

        // printf("HEY\n");

        // printRegisters();

        // printf("\n");

 

        unsigned char op0 = memory[instruction_pointer + 0];

        unsigned char op1 = memory[instruction_pointer + 1];

        unsigned char op2 = memory[instruction_pointer + 2];

 

        instruction_pointer += 3;

        // printf("%c", op0);

 

        switch (op0)

        {

        case 0x00:{

            check_index(op1);

            // load constant

            registers[op1] = op2;

            // printf("0");

            break;

        }

        case 0x01:{

            check_index(op1);

            // add

            registers[op1] += op2;

            // printf("1");

            break;

        }

        case 0x02:

            check_index(op1);

            // subtract

            registers[op1] -= op2;

            // printf("2");

            break;

 

 

        case 0x03:{

           

            check_index(op1);

            // printf("%i", op2);

 

            check_index(op2);

            registers[op1] += registers[op2];

            break;

 

        }

        case 0x04:

            check_index(op1);

            check_index(op2);

            // subtract first and second register values

            registers[op1] -= registers[op2];

            // printf("4");

            break;

 

 

        case 0x05:

            check_index(op1);

            printf("%c", registers[op1]);

            // printf("5");

            break;

 

 

        case 0x06:

            check_index(op1);

            // jump not zero

            if (registers[op1] != 0)

            {

                instruction_pointer = memory[op2];

            }

            else

            {

                // proceed without doing anything

            }

            // printf("6");

            break;

 

 

        case 0x07:

            check_index(op1);

            // jump if zero

            if (registers[op1] == 0)

            {

                instruction_pointer = memory[op2];

            }

            else

            {

                // proceed without doing anything

            }

            // printf("7");

            break;

 

 

        case 0x08:

            check_index(op1);

            check_index(op2);

            //

            registers[op1] = memory[registers[op2]];

            // printf("8");-

            break;

 

 

        case 0x09:

            check_index(op1);

            check_index(op2);

            //

            memory[registers[op1]] = registers[op2];

            // printf("9");

            break;

 

 

        case 0xff:

            //

            printf("break");

 

            break;

        default:

            printf("Illegal instruction\n");

            return -1;

        }

        if (op0 == 0xff){

            break;

        }

    }

 

    return 0;

}

 

int validate(char *hex)

{

    printf("Validating: ");

    while (*hex)

    {

        printf("%c", *hex);

        switch (*hex)

        {

        case '0':

        case '1':

        case '2':

        case '3':

        case '4':

        case '5':

        case '6':

        case '7':

        case '8':

        case '9':

        case 'A':

        case 'a':

        case 'B':

        case 'b':

        case 'C':

        case 'c':

        case 'D':

        case 'd':

        case 'E':

        case 'e':

        case 'F':

        case 'f':

            break;

        default:

        {

            printf(" ..Failed.\n");

            return 0;

        }

        }

        ++hex;

    }

    printf(" ..OK.\n");

    return 1;

}