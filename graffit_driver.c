#include "graffit.c"

/** 
 * Here's some basic testing code. It's primarily intended to give you an idea of
 * how these functions are used.
 *
 * As always, you should add more tests.
 */
int main()
{
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");

    printf("\nTest 1 - Users printed in alphabetical order\n");
    FriendNode *t = allUsers;
    int idx = 0;
    while (t != NULL && t->next != NULL)
    {
        if (strcmp(t->user->name, t->next->user->name) > 0)
        {
            printf("Test 1 failed. Users are not sorted.\n");
            exit(1);
        }

        idx++;
        t = t->next;
    }

    if (idx != 3)
    {
        printf("Test 1 failed. Users were not inserted.\n");
        exit(1);
    }

    printf("Test 1 passed.\n");

    printf("\nTest 2 - Angela adds Brian as a friend\n");
    add_friend(angela, brian);

    // Expect to see Angela with her friend Brian & see Brian with his friend Angela
    if (!in_friend_list(angela->friends, brian) || !in_friend_list(brian->friends, angela))
    {
        printf("Test 2 failed. Friend connection was not made.\n");
        exit(1);
    }

    printf("Test 2 passed.\n");

    printf("\nTest 3 - Degree of connection between Angela and Brian is 1\n");
    int angela_and_brian = get_degrees_of_connection(angela, brian);

    if (angela_and_brian != 1) // Expect 1
    {
        printf("Test 3 failed. Friend connection was not made.\n");
        exit(1);
    }

    printf("Test 3 passed.\n");


    printf("\nTest 4 - Angela follows Brand 'brandonRufino'\n");
    populate_brand_matrix("brands.txt");
    follow_brand(angela, "brandonRufino");

    if (!in_brand_list(angela->brands, "brandonRufino")) // Angela should now follow brandonRufino.
    {
        printf("Test 4 failed. Brand connection was not made.\n");
        exit(1);
    }

    printf("Test 4 passed.\n");

    printf("\nTest 5 - Connect Brands 'brandZero' and 'brandTwo'\n");
    connect_similar_brands("brandZero", "brandTwo");
    int zeroIdx = get_brand_index("brandZero");
    int twoIdx = get_brand_index("brandTwo");

    if (brand_adjacency_matrix[zeroIdx][twoIdx] != 1 || brand_adjacency_matrix[twoIdx][zeroIdx] != 1)
    {
        printf("Test 5 failed. Brand connection was not made.\n");
        exit(1);
    }

    printf("Test 5 passed.\n");

    printf("\nTest 6 - William and Brian have Angela as a mutual friend\n");
    add_friend(angela, william);
    int mutuals_brian_will = get_mutual_friends(brian, william);

    if (mutuals_brian_will != 1) // Expect 1
    {
        printf("Test 6 failed. Mutual friends of Brian and William should be 1.\n");
        exit(1);
    }

    printf("Test 6 passed.\n");

    printf("\nTest 7 - Brian is suggested 1 friend\n");
    User *brianSuggested = get_suggested_friend(brian);

    if (brianSuggested != william) // We should see Will here again
    {
        printf("Test 7 failed. Brian was not suggested William.\n");
        exit(1);
    }

    printf("Test 7 passed.\n");

    printf("\nTest 8 - Mustafa adds 2 suggested friends\n");

    // Expect to see Mustafa with friends Angela, Brian, and Will
    add_friend(angela, mustafa);
    add_suggested_friends(mustafa, 2);

    if (!in_friend_list(mustafa->friends, brian) || !in_friend_list(mustafa->friends, william))
    {
        printf("Test 8 failed. Mustafa was not suggested 2 friends correctly.\n");
        exit(1);
    }

    printf("Test 8 passed.\n");

    printf("\nTest 9 - Mustafa follows 1 suggested brand\n");
    follow_brand(william, "brandTwo");
    follow_brand(mustafa, "brandZero");
    follow_suggested_brands(mustafa, 1);
    // Mustafa should now also follow brandonRufino. A tie is broken against brandTwo.

    if (!in_brand_list(mustafa->brands, "brandonRufino"))
    {
        printf("Test 9 failed. Mustafa did not follow brand 'brandonRufino'.\n");
        exit(1);
    }

    printf("Test 9 passed.\n");

    printf("\nAll basic test cases passed. :)\n");

    //test 10 REMOVE AFTER *****************************************************************************************************************

    User *u1=create_user("user 1"), *u2=create_user("user 2"), *u3=create_user("user 3");
    User *u5=create_user("user 5"), *u6=create_user("user 6");
    User *u7=create_user("user 7"), *u8=create_user("user 8"), *u9=create_user("user 9");
    User *u10=create_user("user 10"), *u11=create_user("user 11"), *u12=create_user("user 12");
    User *u13=create_user("user 13"), *u14=create_user("user 14"), *u15=create_user("user 15");
    User *u16=create_user("user 16");
    add_friend(angela, u1), add_friend(u1, u2), add_friend(mustafa, u3);
    add_friend(u3, u5), add_friend(u3, u6), add_friend(u6, u8);
    add_friend(u8, u9), add_friend(u7, mustafa), add_friend(u7, william);
    add_friend(u7, u9), add_friend(u9, u10), add_friend(u9, u2);
    add_friend(u1, u12), add_friend(u12, u13), add_friend(u15, u11);
    add_friend(u10, u13), add_friend(u11, u14), add_friend(u9, u14);
    int g1=get_degrees_of_connection(brian, u2);
    printf(g1==3?"\nPassed Test 10\n":"\nFailed Test 10\n");
    g1=get_degrees_of_connection(u2, u2);
    printf(g1==0? "Passed Test 10.1\n":"Failed Test 10.1\n");
    g1=get_degrees_of_connection(u2, u1);
    printf(g1==1? "Passed Test 10.2\n":"Failed Test 10.2\n");
    g1=get_degrees_of_connection(u2, mustafa);
    printf(g1==3? "Passed Test 10.3\n":"Failed Test 10.3\n");
    g1=get_degrees_of_connection(u2, u3);
    printf(g1==4? "Passed Test 10.4\n":"Failed Test 10.4\n");
    g1=get_degrees_of_connection(brian, u11);
    printf(g1==5? "Passed Test 11.1\n":"Failed Test 11.1\n");
    g1=get_degrees_of_connection(u3, u13);
    printf(g1==5? "Passed Test 11.2\n":"Failed Test 11.2\n");
    g1=get_degrees_of_connection(u5, u14);
    printf(g1==5? "Passed Test 11.3\n":"Failed Test 11.3\n");
    g1=get_degrees_of_connection(angela, u15);
    printf(g1==6? "Passed Test 11.4\n":"Failed Test 11.4\n");
    g1=get_degrees_of_connection(u6, u16);
    printf(g1==-1? "Passed Test 11.5\n":"Failed Test 11.5\n");
}
