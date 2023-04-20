#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

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
            if (event.value == 0)
            {
                printf("%d", event.code);
            }
        }
        fflush(stdout);
    }

    close(kb_input_device_fd);
    return 0;
}