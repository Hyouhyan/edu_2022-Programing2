#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 256

typedef struct iris{
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char class[64];
}Iris;

int main(void){
    // ファイルを開く
    FILE *fp;
    fp = fopen("./iris.data", "r");
    if(fp == NULL){
        printf("ファイル開けんかったわ\n");
        exit(0);
    }

    Iris p[150];
    int Count = 0;

    // fgets準備
    char line[MAX];

    while(fgets(line, MAX, fp) != NULL){
        sscanf(line, "%f,%f,%f,%f,%s", &p[Count].sepal_length, &p[Count].sepal_width, &p[Count].petal_length, &p[Count].petal_width, p[Count].class);
        Count++;
    }

    // for(int i = 0; i < Count; i++){
    //     printf("iris[%d]:\n", i);
    //     printf("sepal_length:%f\n", p[i].sepal_length);
    //     printf("sepal_width:%f\n", p[i].sepal_width);
    //     printf("petal_length:%f\n", p[i].petal_length);
    //     printf("petal_width:%f\n", p[i].petal_width);
    //     printf("class:%s\n", p[i].class);
    //     printf("\n");
    // }


    Iris avg[3] = {0, 0, 0, 0, ""};
    strcpy(avg[0].class, "Iris-setosa");
    strcpy(avg[1].class, "Iris-versicolor");
    strcpy(avg[2].class, "Iris-virginica");

    Iris sd[3] = {0, 0, 0, 0, ""};
    strcpy(sd[0].class, "Iris-setosa");
    strcpy(sd[1].class, "Iris-versicolor");
    strcpy(sd[2].class, "Iris-virginica");

    int temp, avgCount[3] = {0};

    for(int i = 0; i < Count; i++){
        if(strcmp(p[i].class, "Iris-setosa") == 0)
            temp = 0;
        if(strcmp(p[i].class, "Iris-versicolor") == 0)
            temp = 1;
        if(strcmp(p[i].class, "Iris-virginica") == 0)
            temp = 2;

        avgCount[temp]++;
        
        avg[temp].sepal_length += p[i].sepal_length;
        avg[temp].sepal_width += p[i].sepal_width;
        avg[temp].petal_length += p[i].petal_length;
        avg[temp].petal_width += p[i].petal_width;
    }



    for(int i = 0; i < 3; i++){
        avg[i].sepal_length /= avgCount[i];
        avg[i].sepal_width /= avgCount[i];
        avg[i].petal_length /= avgCount[i];
        avg[i].petal_width /= avgCount[i];
    }

    for(int i = 0; i < Count; i++){
        if(strcmp(p[i].class, "Iris-setosa") == 0)
            temp = 0;
        if(strcmp(p[i].class, "Iris-versicolor") == 0)
            temp = 1;
        if(strcmp(p[i].class, "Iris-virginica") == 0)
            temp = 2;
        
        sd[temp].sepal_length += pow(p[i].sepal_length - avg[temp].sepal_length, 2);
        sd[temp].sepal_width += pow(p[i].sepal_width - avg[temp].sepal_width, 2);
        sd[temp].petal_length += pow(p[i].petal_length - avg[temp].petal_length, 2);
        sd[temp].petal_width += pow(p[i].petal_width - avg[temp].petal_width, 2);
    }

    for(int i = 0; i < 3; i++){
        sd[i].sepal_length = sqrt(sd[i].sepal_length / avgCount[i]); 
        sd[i].sepal_width = sqrt(sd[i].sepal_width / avgCount[i]);
        sd[i].petal_length = sqrt(sd[i].petal_length / avgCount[i]);
        sd[i].petal_width = sqrt(sd[i].petal_width / avgCount[i]);

        printf("%s(avg, sd)\n", avg[i].class);
        printf(" sepal_length:(%f, %f)\n", avg[i].sepal_length, sd[i].sepal_length);
        printf(" sepal_width:(%f, %f)\n", avg[i].sepal_width, sd[i].sepal_width);
        printf(" petal_length:(%f, %f)\n", avg[i].petal_length, sd[i].petal_length);
        printf(" petal_width:(%f, %f)\n", avg[i].petal_width, sd[i].petal_width);
    }

    fclose(fp);
    return 0;
}