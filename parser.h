#ifndef __AT_COMMAND_PARSER__
#define __AT_COMMAND_PARSER__

#include <stdint.h>

#define AT_COMMAND_MAX_LINES 100
#define AT_COMMAND_MAX_LINE_SIZE 100




typedef struct parser
{
    uint8_t data[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE];
    uint8_t line_count;
    uint8_t col_count;
    uint8_t status;
}AT_COMMAND_DATA;

AT_COMMAND_DATA date;

typedef enum{
    STATE_MACHINE_NOT_READY,
    STATE_MACHINE_READY_OK,
    STATE_MACHINE_READY_WITH_ERROR

}STATE_MACHINE_RETURN_VALUE;

STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t char_crt);

#endif // !__AT_COMMAND_PARSER__