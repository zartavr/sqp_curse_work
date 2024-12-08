#include "list.h"
#include "person.h"

// For debug
extern void _node_print(void *data);
extern void _list_node_foreach(List *list, foreach_cb callback);

void person_print(void *data)
{
    Person *user = data;
    printf("id: %d\t name: %s\t age: %d\t height: %d\t weight: %d\n",
           user->id,
           user->name,
           user->age,
           user->height,
           user->weight);
}

bool filter_id(void *data)
{
    Person *user = data;
    if (user->id % 2 == 0)
    {
        return true;
    }
    return false;
}

bool swap_id(void *prev, void *current)
{
    Person *user_id_greater = prev;
    Person *user_id_less = current;
    if (user_id_greater->id < user_id_less->id)
    {
        return true;
    }
    return false;
}

void save_list(List *list)
{
    FILE *fout_ptr;
    fout_ptr = fopen("test_save", "wb");
    list_save(list, fout_ptr);
    fclose(fout_ptr);
}

void load_list(List *list)
{
    FILE *fin_ptr;
    fin_ptr = fopen("test_save", "rb");
    list_load(list, fin_ptr);
    fclose(fin_ptr);
}

int main()
{
    List person_list = {};

    List* null_list_ptr = NULL;

    for (size_t i = 0; i < 10; i++)
    {
        Person user = {
            .id = i,
            .age = 20 + i * 2,
            .weight = 50 + i * 3,
            .height = 50 + i * 3 + 100};
        sprintf(user.name, "user%ld", i);

        list_push(&person_list, &user, sizeof(user));
    }

    save_list(&person_list);

    load_list(&person_list);

    printf("list len: %d\n", list_get_node_count(&person_list));

    _list_node_foreach(&person_list, _node_print);
    list_foreach(&person_list, NULL);

    list_filter(&person_list, &person_list, filter_id);

    printf("list len: %d\n", list_get_node_count(&person_list));
    list_foreach(&person_list, person_print);

    save_list(&person_list);

    load_list(&person_list);

    list_foreach(&person_list, person_print);

    return 0;
}