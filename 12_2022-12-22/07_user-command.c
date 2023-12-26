#include<stdio.h>
#include<stdlib.h>

typedef struct elem{
    int num;
    struct elem *next;
}Elem;

void print_list(Elem *root){
    while(root != NULL){
        printf("%d\n", root -> num);
        root = root -> next;
    }
}

Elem* add_elem(Elem *root, int num){
    Elem *next = root;

    Elem *p = (Elem*)malloc(sizeof(Elem));
    p -> num = num;

    if(root == NULL){
        p -> next = root;

        return p;
    }else{
        Elem *back = NULL;
        while(next != NULL && next -> num < num){
            back = next;
            next = next -> next;
        }

        p -> next = next;

        if(back != NULL){
            back -> next = p;
            return root;    
        }
        
        return p;
    }
}

void free_list(Elem *root){
    Elem *nextp;
    while(root != NULL){
        nextp = root -> next;
        free(root);
        root = nextp;
    }
}

Elem* delete_elem(Elem *root, int delnum){
    Elem *delp = root, *back = NULL;

    if(delp == NULL){
        printf("リストに要素は存在しません\n");
        return root;
    }

    while(delp -> num != delnum){
        back = delp;
        delp = delp -> next;
        if(delp == NULL){
            printf("該当要素は存在しません\n");
            return root;
        }
    }

    if(back != NULL){
        back -> next = delp -> next;
        free(delp);
        return root;
    }else{
        Elem *nextroot = delp -> next;
        free(delp);
        return nextroot;
    }
}

int main(void){
    Elem *root = NULL;

    int flg = 1;

    char command;
    int num;

    while(flg){
        scanf("%c", &command);
        if(command == 'a' | command == 'd')
            scanf("%d", &num);

        switch (command){
            case 'a':
                root = add_elem(root, num);
                break;
            
            case 'd':
                root = delete_elem(root, num);
                break;
            
            case 'p':
                print_list(root);
                break;
            
            case 'q':
                free_list(root);
                flg = 0;
                break;
        }
    }

    return 0;
}