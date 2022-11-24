/**
 * CSC A48 - Intro to Computer Science II, Summer 2021
 * 
 * Assignment 3 - Graffit
 * 
 * Graphs &
 * Recursion
 * Assignment
 * For
 * Freshmen
 * In
 * Toronto
 *
 * (I am so proud of that initialism.)
 * 
 * This is the program file where you will implement your solution for
 * Assignment 3. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will also need to have read the handout carefully. 
 * 
 * Parts where you have to implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive
 * and will check that your solution is *correct*, not only that it
 * provides functionality.
 * 
 * (c) 2020 William Song, Mustafa Quraish
 * (c) 2021 Charles Xu
 **/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3 // A small graph
#endif

typedef struct user_struct
{
  char name[MAX_STR_LEN];
  struct friend_node_struct *friends;
  struct brand_node_struct *brands;
  bool visited;
} User;

typedef struct friend_node_struct
{
  User *user;
  struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct
{
  char brand_name[MAX_STR_LEN];
  struct brand_node_struct *next;
} BrandNode;

FriendNode *allUsers = NULL;

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

typedef struct queue
{
  User *user[MAX_STR_LEN];
  int size;
} queue;


/**
 * Given the head to a FriendNode linked list, returns true if a
 * given user's name exists in the list. Returns false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node)
{
  for (FriendNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->user->name, node->name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a BrandNode linked list, returns true if a
 * given brand's name exists in the list. Returns false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name)
{
  for (BrandNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->brand_name, name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a FriendNode linked list, inserts a given user
 * into the linked list and returns the head of the new linked list.
 * The insertion is done in alphabetical order. If the user already
 * exists, no modifications are made and the list is returned as is.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (in_friend_list(head, node))
  {
    printf("User already in list\n");
    return head;
  }

  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->user->name, node->name) > 0)
  {
    fn->next = head;
    return fn;
  }

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a BrandNode linked list, inserts a given brand into
 * the linked list and returns the head of the new linked list. The
 * insertion is done in alphabetical order. If the brand already exists,
 * no modifications are made and the list is returned as is.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (in_brand_list(head, node))
  {
    printf("Brand already in list\n");
    return head;
  }

  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->brand_name, node) > 0)
  {
    fn->next = head;
    return fn;
  }

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a FriendNode linked list, removes a given user from
 * the linked list and returns the head of the new linked list. If the user
 * does not exist, no modifications are made and the list is returned as is.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (!in_friend_list(head, node))
  {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0)
  {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given the head to a BrandNode linked list, removes a given brand from
 * the linked list and returns the head of the new linked list. If the brand
 * does not exist, no modifications are made and the list is returned as is.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (!in_brand_list(head, node))
  {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0)
  {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given a user, prints their name, friends, and liked brands.
 */
void print_user_data(User *user)
{
  printf("User name: %s\n", user->name);

  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next)
  {
    printf("   %s\n", f->user->name);
  }

  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next)
  {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Given a brand, returns the index of the brand inside the brand_names array.
 * If it doesn't exist in the array, return -1
 */
int get_brand_index(char *name)
{
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (strcmp(brand_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("Brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Given a brand, prints their name, index (inside the brand_names
 * array), and the names of other similar brands.
 */
void print_brand_data(char *brand_name)
{
  int idx = get_brand_index(brand_name);
  if (idx < 0)
  {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }

  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);

  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0)
    {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char *file_name)
{
  // Read the file
  char buff[MAX_STR_LEN];
  FILE *f = fopen(file_name, "r");
  fscanf(f, "%s", buff);
  char *line = buff;
  // Load up the brand_names matrix
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (i == MAT_SIZE - 1)
    {
      strcpy(brand_names[i], line);
      break;
    }
    int index = strchr(line, ',') - line;
    strncpy(brand_names[i], line, index);
    line = strchr(line, ',') + sizeof(char);
  }
  // Load up the brand_adjacency_matrix
  for (int x = 0; x < MAT_SIZE; x++)
  {
    fscanf(f, "%s", buff);
    for (int y = 0; y < MAT_SIZE; y++)
    {
      int value = (int)buff[y * 2];
      if (value == 48)
      {
        value = 0;
      }
      else
      {
        value = 1;
      }
      brand_adjacency_matrix[x][y] = value;
    }
  }
}

/**
 * TODO: Complete this function
 * Creates and returns a user.
 */
User *create_user(char *name)
{
  User *new_user_node = (User*)calloc(1, sizeof(User));
  strcpy(new_user_node->name, name);
  new_user_node->friends = NULL;
  new_user_node->brands = NULL;
  new_user_node->visited = false;

  if (in_friend_list(allUsers, new_user_node))
  {
    return NULL;
  }

  allUsers = insert_into_friend_list(allUsers, new_user_node);
  return new_user_node;
}

/**
 * TODO: Complete this function
 * Deletes a given user.
 */
int delete_user(User *user)
{
  int val = -1;
  if (in_friend_list(allUsers, user) && user != NULL)
  {
    for (BrandNode *brand = user->brands; brand != NULL; brand = brand->next)
    {
      user->brands = delete_from_brand_list(user->brands, brand->brand_name);
    }

    FriendNode *ptr = allUsers;
    while (ptr != NULL)
    {
      if (in_friend_list(ptr->user->friends, user))
      {
        ptr->user->friends = delete_from_friend_list(ptr->user->friends, user);
      }
      ptr = ptr->next;
    }
    allUsers = delete_from_friend_list(allUsers, user);
    free(user);
    val = 0;
  }
  return val;
}

/**
 * TODO: Complete this function
 * Create a friendship between user and friend.
 */
int add_friend(User *user, User *friend)
{
  if (in_friend_list(user->friends, friend) || in_friend_list(friend->friends, user) == 1)
  {
    return -1;
  }

  user->friends = insert_into_friend_list(user->friends, friend);
  friend->friends = insert_into_friend_list(friend->friends, user);
  return 0;
}

/**
 * TODO: Complete this function
 * Removes a friendship between user and friend.
 */
int remove_friend(User *user, User *friend)
{
  if (!in_friend_list(friend->friends, user) || !in_friend_list(user->friends, friend))
  {
    return -1;
  }
  else
  {
    user->friends = delete_from_friend_list(user->friends, friend);
    friend->friends = delete_from_friend_list(friend->friends, user);
    return 0;
  }
}

/**
 * TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 */
int follow_brand(User *user, char *brand_name)
{
  if (in_brand_list(user->brands, brand_name) || get_brand_index(brand_name) == -1)
  {
    return -1;
  }
  else
  {
    user->brands = insert_into_brand_list(user->brands, brand_name);
    return 0;
  }
}

/**
 * TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 */
int unfollow_brand(User *user, char *brand_name)
{
  if (!in_brand_list(user->brands, brand_name) || get_brand_index(brand_name) == -1)
  {
    return -1;
  }
  FriendNode *ptr = allUsers;
  if (ptr == NULL)
  {
    return -1;
  }
  while (ptr != NULL)
  {
    if (strcmp(ptr->user->name, user->name) == 0)
    {
      ptr->user->brands = delete_from_brand_list(ptr->user->brands, brand_name);
      return 0;
    }
    ptr = ptr->next;
  }
  return -1;
}

/**
 * TODO: Complete this function
 * Return the number of mutual friends between two users.
 */
int get_mutual_friends(User *a, User *b)
{
  FriendNode *counter = a->friends;
  int total_friends = 0;

  while (counter != NULL)
  {
    if (in_friend_list(b->friends, counter->user))
    {
      total_friends++;
    }
    counter = counter->next;
  }
  return total_friends;
}

/**
 * TODO: Complete this function
 * A degree of connection is the number of steps it takes to get from
 * one user to another. Returns a non-negative integer representing
 * the degrees of connection between two users.
 */

int getindex(User *a)
{
  int i = 0;
  for(FriendNode *current = allUsers; current != NULL; current = current->next)
  {
    if (current->user == a)
    {
      return i;
    }
    i++;
  }
  return -1;
}

int getlength(FriendNode *friend)
{
  int i = 0;
  for (FriendNode *current = allUsers; current != NULL; current = current->next)
  {
    i++;
  }
  return i;
}

FriendNode *getfriends(User *user)
{
  for (FriendNode *current = allUsers; current != NULL; current = current->next)
  {
    if (current->user == user)
    {
      return current;
    }
  }
  return NULL;
}

void createqueue(queue *q)
{
  q->size = 0;
}

void enqueue(queue *q, User *a)
{
  q->user[q->size] = a;
  q->size += 1;
}

User *dequeue(queue *q)
{
  User *final = q->user[0];
  for (int i = 0; i < (q->size - 1); i++)
  {
    q->user[i] = q->user[i+1];
  }
  q->size -= 1;
  return final;
}

bool isempty(queue *q)
{
  return q->size == 0;
}

void init_array(int distance[getlength(allUsers)])
{
  for (int i = 0; i < getlength(allUsers); i++)
  {
    distance[i] = -1;
  }
}

void setuserfalse()
{
  for (FriendNode *current = allUsers; current != NULL; current = current->next)
  {
    current->user->visited = false;
  }
}

int get_degrees_of_connection(User *a, User *b) /////////////// PROB WRONG FIX
{
  int degree;
  if (a == NULL || b == NULL || !in_friend_list(allUsers, a) || !in_friend_list(allUsers, b))
  {
    return -1;
  }
  else if(a == b)
  {
    return 0;
  }
  else
  {
    int storedistances[getlength(allUsers)];
    init_array(storedistances);

    queue q;
    createqueue(&q);
    enqueue(&q, a);

    int index_a = getindex(a);
    storedistances[index_a] = 0;

    while (!isempty(&q))
    {
      User *currentuser = dequeue(&q);
      for (FriendNode *currentfriend = currentuser->friends; currentfriend != NULL; currentfriend = currentfriend->next)
      {
        if (storedistances[getindex(currentfriend->user)] == -1 && !(currentfriend->user->visited))
        {
          storedistances[getindex(currentfriend->user)] = storedistances[getindex(currentuser)] + 1;
          currentuser->visited = true;
          enqueue(&q, currentfriend->user);
        }
      }
    }
    degree = storedistances[getindex(b)];
    setuserfalse();
  }
  return degree;
}

// /**
//  * TODO: Complete this function
//  * Marks two brands as similar.
//  */

void connect_similar_brands(char *brandNameA, char *brandNameB)
{
  if (get_brand_index(brandNameA) == -1 || get_brand_index(brandNameB) == -1)
  {
    return;
  }

  int j = get_brand_index(brandNameB);
  int i = get_brand_index(brandNameA);
  brand_adjacency_matrix[i][j] = 1;
  brand_adjacency_matrix[j][i] = 1;
}

/**
 * TODO: Complete this function
 * Marks two brands as not similar.
 */
void remove_similar_brands(char *brandNameA, char *brandNameB)
{
  if (get_brand_index(brandNameA) == -1 || get_brand_index(brandNameB) == -1)
  {
    return;
  }
  int row = get_brand_index(brandNameA);
  int col = get_brand_index(brandNameB);
  brand_adjacency_matrix[row][col] = 0;
  brand_adjacency_matrix[col][row] = 0;
}

/**
 * TODO: Complete this function
 * Returns a suggested friend for the given user.
 */

int mutual_brands(User *a, User *b)
{
  int flag = 0;
  if (a == NULL || b == NULL || !in_friend_list(allUsers, a) || !(in_friend_list(allUsers, b)))
  {
    return 0;
  }
  else
  {
    for (BrandNode *brand_a = a->brands; brand_a != NULL; brand_a = brand_a->next)
    {
      for (BrandNode *brand_b = b->brands; brand_b != NULL; brand_b = brand_b->next)
      {
        if (strcmp(a->brands->brand_name, b->brands->brand_name) == 0)
        {
          flag++;
        }
      }
    }
  }
  return flag;
}



User *get_suggested_friend(User *user)
{
  int mutuals = 0;
  User *finaluser = NULL;
  if (user != NULL && in_friend_list(allUsers, user))
  {
    for (FriendNode *user_friend = allUsers; user_friend != NULL; user_friend = user_friend->next)
    {
      if (!(in_friend_list(user->friends, user_friend->user)) && user != user_friend->user)
      {
        if (mutuals < mutual_brands(user, user_friend->user))
        {
          mutuals = mutual_brands(user, user_friend->user);
          finaluser = user_friend->user;
        }
        else if(mutuals == mutual_brands(user, user_friend->user))
        {
          if (finaluser != NULL && strcmp(user_friend->user->name, finaluser->name ) > 0)
          {
            finaluser = user_friend->user;
          }
          else
          {
            finaluser = user_friend->user;
          }
        }
      }
    }
  }
  return finaluser;
}

/**
 * TODO: Complete this function
 * Adds n suggested friends for the given user.
 * Returns how many friends were successfully followed.
 */
int add_suggested_friends(User *user, int n)
{
  int numfriends = 0;
  if (user == NULL)
  {
    return 0;
  }
  else {
    for (int i = 0; i < n; i++)
    {
      if (add_friend(user, get_suggested_friend(user)) == 0)
      {
        numfriends += 1;
      }
    }
  }
  return numfriends;
}

/**
 * TODO: Complete this function
 * Follows n suggested brands for the given user.
 * Returns how many brands were successfully followed.
 */
int follow_suggested_brands(User *user, int n)
{
  if (user == NULL)
  {
    return 0;
  }
  if (strcmp(user->name, "") == 0)
  {
    return 0;
  }
  if (!in_friend_list(allUsers, user) || n <= 0)
  {
    return 0;
  }

  int numbrands = 0;
  int flag = 0;
  char suggested[MAX_STR_LEN];

  while (flag != n)
  {
    int similar = 0;
    strcpy(suggested, "");
    for (int i = 0; i < MAT_SIZE; i++)
    {
      int count = 0;
      BrandNode* ptr = user->brands;
      if (!in_brand_list(ptr, brand_names[i]))
      {
        while (ptr != NULL)
        {
          if (brand_adjacency_matrix[i][get_brand_index(ptr->brand_name)] == 1)
          {
            count++;
          }
          ptr = ptr->next;
        }
        if (strcmp(suggested, "") == 0)
        {
          strcpy(suggested, brand_names[i]);
        }
        if (count > similar)
        {
          similar = count;
          strcpy(suggested, "");
          strcpy(suggested, brand_names[i]);
        }
        else if(count == similar)
        {
          if (strcmp(brand_names[i], suggested) > 0)
          {
            strcpy(suggested, "");
            strcpy(suggested, brand_names[i]);
          }
        }
      }
    }
    if (strcmp(suggested, "") != 0)
    {
      follow_brand(user, suggested);
      numbrands++;
    }
    flag++;
  }
  return numbrands;
}
