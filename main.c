#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define NUM_KEY_CODES 122

const char *map_key_codes[] = {
    "RESERVED",
    "ESC",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "MINUS",
    "EQUAL",
    "BACKSPACE",
    "TAB",
    "Q",
    "W",
    "E",
    "R",
    "T",
    "Y",
    "U",
    "I",
    "O",
    "P",
    "LEFTBRACE",
    "RIGHTBRACE",
    "ENTER",
    "LEFTCTRL",
    "A",
    "S",
    "D",
    "F",
    "G",
    "H",
    "J",
    "K",
    "L",
    "SEMICOLON",
    "APOSTROPHE",
    "GRAVE",
    "LEFTSHIFT",
    "BACKSLASH",
    "Z",
    "X",
    "C",
    "V",
    "B",
    "N",
    "M",
    "COMMA",
    "DOT",
    "SLASH",
    "RIGHTSHIFT",
    "KPASTERISK",
    "LEFTALT",
    "SPACE",
    "CAPSLOCK",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "NUMLOCK",
    "SCROLLLOCK",
    "KP7",
    "KP8",
    "KP9",
    "KPMINUS",
    "KP4",
    "KP5",
    "KP6",
    "KPPLUS",
    "KP1",
    "KP2",
    "KP3",
    "KP0",
    "KPDOT",
    "UNSPECIFIED",
    "ZENKAKUHANKAKU",
    "102ND",
    "F11",
    "F12",
    "RO",
    "KATAKANA",
    "HIRAGANA",
    "HENKAN",
    "KATAKANAHIRAGANA",
    "MUHENKAN",
    "KPJPCOMMA",
    "KPENTER",
    "RIGHTCTRL",
    "KPSLASH",
    "SYSRQ",
    "RIGHTALT",
    "LINEFEED",
    "HOME",
    "UP",
    "PAGEUP",
    "LEFT",
    "RIGHT",
    "END",
    "DOWN",
    "PAGEDOWN",
    "INSERT",
    "DELETE",
    "MACRO",
    "MUTE",
    "VOLUMEDOWN",
    "VOLUMEUP",
    "POWER",
    "KPEQUAL",
    "KPPLUSMINUS",
    "PAUSE",
    "SCALE",
    "KPCOMMA"
};

int loop = 1;

void sig_handler()
{
    loop = 0;
}

int main(int argc, char **argv)
{
    char *kb_input_device = "/dev/input/event4";
    int kb_input_device_fd = -1;
    struct input_event event;

    signal(SIGINT, sig_handler);

    if ((kb_input_device_fd = open(kb_input_device, O_RDONLY)) == -1)
    {
        fprintf(stderr, "Couldn't open the device file <%s>.", kb_input_device);
        return -1;
    }

    while (loop)
    {
        read(kb_input_device_fd, &event, sizeof(struct input_event));

        if (event.type == EV_KEY)
        {
            if (event.value == 0 && event.code < NUM_KEY_CODES)
            {
                printf("Key <%s> with code <%d>\n", map_key_codes[event.code], event.code);
            }
        }
    }

    close(kb_input_device_fd);
    return 0;
}