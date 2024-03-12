#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_STATES 8

typedef struct state
{
    int id;
    int transition_zero;
    int transition_one;
} state;

state **state_machine;
state *current_state;
state **unreachable_states;
int num_unreachable_states;

void change_transition(int input, int transition)
{
    if (transition == 1)
        current_state->transition_one = input;
    else if (transition == 0)
        current_state->transition_zero = input;
}

void print_state_machine()
{
    for (int i = 0; i < MAX_STATES; i++)
        printf("%d %d %d\n", state_machine[i]->id,
               state_machine[i]->transition_zero,
               state_machine[i]->transition_one);
}

void update_current_state(int input)
{
    if (input == 1)
    {
        current_state = state_machine[current_state->transition_one];
    }
    else if (input == 0)
    {
        current_state = state_machine[current_state->transition_zero];
    }
    printf("%d\n", current_state->id);
}

void initialize_state_machine()
{
    state_machine = (state **)calloc(sizeof(state *), MAX_STATES);
    unreachable_states = (state **)calloc(sizeof(state *), MAX_STATES);
    int zeros[MAX_STATES] = {3, 1, 1, 0, 2, 5, 4, 3};
    int ones[MAX_STATES] = {5, 2, 6, 4, 2, 0, 1, 0};
    for (int i = 0; i < MAX_STATES; i++)
    {
        state_machine[i] = (state *)malloc(sizeof(state));
        state_machine[i]->id = i;
        state_machine[i]->transition_zero = zeros[i];
        state_machine[i]->transition_one = ones[i];
    }
}

void collect_unreachable_states()
{
    bool reachable[MAX_STATES] = {false};
    reachable[current_state->id] = true;

    for (int i = 0; i < MAX_STATES; i++)
    {
        if (reachable[i])
        {
            reachable[state_machine[i]->transition_zero] = true;
            reachable[state_machine[i]->transition_one] = true;
        }
    }

    num_unreachable_states = 0;
    for (int i = 0; i < MAX_STATES; i++)
    {
        if (!reachable[i])
        {
            unreachable_states[num_unreachable_states++] = state_machine[i];
        }
    }
}

void print_unreachable_states()
{
    if (num_unreachable_states == 0)
    {
        printf("No garbage\n");
    }
    else
    {
        printf("Garbage:");
        for (int i = 0; i < num_unreachable_states; i++)
        {
            printf(" %d", unreachable_states[i]->id);
        }
        printf("\n");
    }
}

void delete_unreachable_states()
{
    if (num_unreachable_states == 0)
    {
        printf("No states deleted\n");
    }
    else
    {
        printf("Deleted:");
        for (int i = 0; i < num_unreachable_states; i++)
        {
            printf(" %d", unreachable_states[i]->id);
            free(unreachable_states[i]);
        }
        printf("\n");
        num_unreachable_states = 0;
    }
}

int main(int argc, char *argv[])
{
    bool running = true;
    char command[10];
    initialize_state_machine();
    current_state = state_machine[0];
    printf("%d\n", current_state->id);

    while (running)
    {
        printf("Enter a command: ");
        scanf("%s", command);
        switch (command[0])
        {
        case 'c':
            change_transition(command[4] - '0', command[2] - '0');
            break;
        case 'g':
            collect_unreachable_states();
            print_unreachable_states();
            break;
        case 'd':
            if (command[1] == '\0')
            {
                collect_unreachable_states();
                delete_unreachable_states();
            }
            else
            {
                int state_to_delete = command[1] - '0';
                if (state_to_delete == current_state->id)
                {
                    printf("Not deleted\n");
                }
                else
                {
                    bool is_reachable = false;
                    for (int i = 0; i < MAX_STATES; i++)
                    {
                        if (state_machine[i]->transition_zero == state_to_delete ||
                            state_machine[i]->transition_one == state_to_delete)
                        {
                            is_reachable = true;
                            break;
                        }
                    }
                    if (is_reachable)
                    {
                        printf("Not deleted\n");
                    }
                    else
                    {
                        printf("Deleted\n");
                        free(state_machine[state_to_delete]);
                    }
                }
            }
            break;
        case 'p':
            print_state_machine();
            break;
        case '0':
        case '1':
            update_current_state(command[0] - '0');
            break;
        case 'q':
            running = false;
            break;
        default:
            printf("Invalid command. Please try again.\n");
            break;
        }
    }
    return 0;
}