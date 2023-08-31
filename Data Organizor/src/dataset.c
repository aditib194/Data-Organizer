#include <dataset.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int category_add(Category dataset[], int number_of_categories, FileData files[],
                 int number_of_files, const char* file_name) {
  // TODO
  //changed dataset[j]->list to dataset[j].list
  int add = 0;
  for(int i = 0; i < number_of_files; i++) {
    if(strcmp(files[i].file_name, file_name) == 0) {
      char* can = files[i].category;

      //Traverse through Dataset to find category
      for(int j = 0; j < number_of_categories; j++) {
        if(strcmp(dataset[j].name, can) == 0) {
          FileNode* current = dataset[j].list;

          //empty list
          if(current == NULL) {
            struct FileNode *new = malloc(sizeof(struct FileNode));
            new->file = &files[i];
            new->next = NULL;
            dataset[j].list = new;
            add = 1;
            break;
          }

          //beginning of one node list
          if(strcmp(current->file->file_name, file_name) > 0) {
            struct FileNode *new = malloc(sizeof(struct FileNode));
            new->file = &files[i];
            new->next = current;
            dataset[j].list = new;
            add = 1;
            break;
          }

          FileNode* next = current->next;
          while(next != NULL && strcmp(next->file->file_name, file_name) <= 0) {
            current = next;
            next = current->next;
          }
          if(strcmp(current->file->file_name, file_name) == 0) {
            break;
          }
          if(next == NULL) {
            struct FileNode *new = malloc(sizeof(struct FileNode));
            new->file = &files[i];
            new->next = NULL;
            current->next = new;
            add = 1;
            break;
          }
          struct FileNode *new = malloc(sizeof(struct FileNode));
          new->file = &files[i];
          new->next = next;
          current->next = new;
          add = 1;
          break;
        }
      }
    }
  }
  return add;
}

FileData* category_remove(Category dataset[], int number_of_categories,
                          const char* category, const char* file_name) {
  // TODO
for(int i = 0; i < number_of_categories; i++) {
  if(strcmp(dataset[i].name, category) == 0) {
    FileNode* current = dataset[i].list;

    if(current == NULL) {
      return NULL;
    }
    if(strcmp(current->file->file_name, file_name) == 0) {
      if(current->next == NULL) {
        dataset[i].list = NULL;
        return current->file;
      } else {
        dataset[i].list = current->next;
        return current->file;
      }
    }

    FileNode* next = current->next;
    while(next != NULL && strcmp(next->file->file_name, file_name) != 0) {
      current = next;
      next = next->next;
    }
    if(next == NULL) {
      return NULL;
    }
    current->next = next->next;
    return next->file;

  }
}
return NULL;
}


FileData* category_change(Category dataset[], int number_of_categories,
                          FileData files[], int number_of_files,
                          const char* file_name, const char* old_category,
                          const char* new_category) {
  for(int i = 0; i < number_of_files; i++) {
    if(strcmp(files[i].file_name, file_name) == 0) {
      struct FileData* target = &files[i];
      if(strcmp(files[i].category, old_category) == 0) {
        category_remove(dataset, number_of_categories, old_category, file_name);
        files[i].category = new_category;
        category_add(dataset, number_of_categories, files, number_of_files, file_name);
        return target;
      }
      //files[i].category = new_category;
      //return target;
      return NULL;
    }
  }
}

