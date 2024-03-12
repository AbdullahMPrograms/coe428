#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_STATES 8

typedef struct state
{
    char id;
    char transition_zero;
    char transition_one;
} state_t;

state_t **state_machine;
state_t *current_state;
state_t **unreachable_states;
int num_unreachable_states;

void change_transition(char input, char transition)
{
    if (transition == '1')
        current_state->transition_one = input;
    else if (transition == '0')
        current_state->transition_zero = input;
}

void print_state_machine()
{
    for (int i = 0; i < MAX_STATES; i++)
        printf("%c %c %c\n", state_machine[i]->id,
               state_machine[i]->transition_zero,
               state_machine[i]->transition_one);
}

void update_current_state(char input)
{
    if (input == '1')
    {
        current_state = state_machine[current_state->transition_one - 'A'];
    }
    else if (input == '0')
    {
        current_state = state_machine[current_state->transition_zero - 'A'];
    }
    printf("%c\n", current_state->id);
}

void initialize_state_machine()
{
    state_machine = (state_t **)calloc(sizeof(state_t *), MAX_STATES);
    unreachable_states = (state_t **)calloc(sizeof(state_t *), MAX_STATES);
    char zeros[MAX_STATES] = {'F', 'H', 'G', 'C', 'B', 'D', 'E', 'A'};
    char ones[MAX_STATES] = {'B', 'C', 'H', 'F', 'A', 'G', 'G', 'D'};
    for (int i = 0; i < MAX_STATES; i++)
    {
        state_machine[i] = (state_t *)malloc(sizeof(state_t));
        state_machine[i]->id = 'A' + i;
        state_machine[i]->transition_zero = zeros[i];
        state_machine[i]->transition_one = ones[i];
    }
}

void collect_unreachable_states()
{
    bool reachable[MAX_STATES] = {false};
    reachable[current_state->id - 'A'] = true;

    for (int i = 0; i < MAX_STATES; i++)
    {
        if (reachable[i])
        {
            reachable[state_machine[i]->transition_zero - 'A'] = true;
            reachable[state_machine[i]->transition_one - 'A'] = true;
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
            printf(" %c", unreachable_states[i]->id);
        }
        printf("\n");
    }
}

void delete_unreachable_states() {
    if (num_unreachable_states == 0) {
        printf("No states deleted\n");
    } else {
        printf("Deleted:");
        for (int i = 0; i < num_unreachable_states; i++) {
            char state_to_delete = unreachable_states[i]->id;
            printf(" %c", state_to_delete);
            int state_index = state_to_delete - 'A';
            free(state_machine[state_index]);
            for (int j = state_index; j < MAX_STATES - 1; j++) {
                state_machine[j] = state_machine[j + 1];
            }
            state_machine[MAX_STATES - 1] = NULL;
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
    printf("%c\n", current_state->id);

    while (running)
    {
        printf("Enter a command: ");
        scanf("%s", command);
        switch (command[0])
        {
        case 'c':
            change_transition(command[2], command[1]);
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
                char state_to_delete = command[1];
                if (state_to_delete == current_state->id)
                {
                    printf("Not deleted\n");
                }
                else
                {
                    bool is_reachable = false;
                    for (int i = 0; i < MAX_STATES; i++)
                    {
                        if (state_machine[i] != NULL &&
                            (state_machine[i]->transition_zero == state_to_delete ||
                             state_machine[i]->transition_one == state_to_delete))
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
                        int state_index = state_to_delete - 'A';
                        free(state_machine[state_index]);
                        for (int i = state_index; i < MAX_STATES - 1; i++)
                        {
                            state_machine[i] = state_machine[i + 1];
                        }
                        state_machine[MAX_STATES - 1] = NULL;
                    }
                }
            }
            break;
        case 'p':
            print_state_machine();
            break;
        case '0':
        case '1':
            update_current_state(command[0]);
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