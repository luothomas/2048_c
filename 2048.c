#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 4

int box[size][size];

void initialize(){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            box[i][j] = 0;
        }
    }
}
void tutorials(){
    printf("==============================");
    printf("\nWelcome to 2048 arcade!!!");
    printf("\nenter 'wasd' to move the board");
    printf("\n'w'stands for moving upward");
    printf("\n'a'stands for moving leftward");
    printf("\n's'stands for moving downward");
    printf("\n'd'stands for moving rightward");
    printf("\n==============================\n");
}
void print_box(){
    printf("----- ---- ---- -----\n");
    
    for(int i = 0; i < size; i++){
        printf("|");
        for (int j = 0; j < size; j++){
            printf("%4d|", box[i][j]);
        }
        printf("\n----- ---- ---- -----\n");
    }
}
void merge_boxes(int a, int b, int c, int d){
//原本打算把相加部分併在移動部分
//後來發現太過冗長, 拆分至另一個副程式
    box[c][d] += box[a][b];
    box[a][b] = 0;
}
void move_up(){//向上移動
    int i, j;
    for (j = 0; j < size; j++){
        for (i = 1; i < size; i++){//由上而下檢查各格子
            if (box[i][j] != 0){
                int temp = i;
                while (temp > 0 && box[temp-1][j] == 0){//如果上方格子等於0, 向上移
                    box[temp-1][j] = box[temp][j];
                    box[temp][j] = 0;
                    temp--;
                }
                if (temp > 0 && box[temp-1][j] == box[temp][j]){//如果上方格子數值與自己相同, 向上合併
                    merge_boxes(temp, j, temp-1, j);
                }
            }
        }
    }
}

void move_down(){//向下移動
    int i, j;
    for (j = 0; j < size; j++){
        for (i = size - 2; i >= 0; i--){
            if (box[i][j] != 0){
                int temp = i;
                while (temp < size - 1 && box[temp+1][j] == 0){//如果下方格子等於0, 向下移
                    box[temp+1][j] = box[temp][j];
                    box[temp][j] = 0;
                    temp++;
                }
                if (temp < size - 1 && box[temp+1][j] == box[temp][j]){
                    merge_boxes(temp, j, temp+1, j);
                }
            }
        }
    }
}

void move_left(){//向左移動
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 1; j < size; j++){
            if (box[i][j] != 0){
                int temp = j;
                while (temp > 0 && box[i][temp-1] == 0){
                    box[i][temp-1] = box[i][temp];
                    box[i][temp] = 0;
                    temp--;
                }
                if (temp > 0 && box[i][temp-1] == box[i][temp]){
                    merge_boxes(i, temp, i, temp-1);
                }
            }
        }
    }
}

void move_right()
{
    int i, j;
    for (i = 0; i < size; i++){
        for (j = size - 2; j >= 0; j--){
            if (box[i][j] != 0){
                int temp = j;
                while (temp < size - 1 && box[i][temp+1] == 0){
                    box[i][temp+1] = box[i][temp];
                    box[i][temp] = 0;
                    temp++;
                }
                if (temp < size-1 && box[i][temp+1] == box[i][temp]){
                    merge_boxes(i, temp, i, temp+1);
                }
            }
        }
    }
}

void generate_number(){//隨機生成2或4
    int gen_num = 2 * (rand()%2+1);
    while(1){
        int i = rand()%(size);
        int j = rand()%(size);
        while(box[i][j] == 0){
            box[i][j] += gen_num;
            break;
        }
        break;
    }
}

int full_check(){//檢查是否滿板
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(box[i][j] == 0){
                return 0;
                break;
            }
        }
    }
    return 1;
}
int win_check(){
    for(int i = 0; i<size; i++){
        for(int j = 0; j < size; j++){
            if(box[i][j] == 2048){
                return 1;
                break;
            }
        }
    }
    return 0;
}
int main(){
    tutorials();
    srand(time(NULL));
    initialize();
    generate_number();
    generate_number();
    char move;
    while (1){
        print_box();
        printf("Enter your move (w/a/s/d): ");
        scanf(" %c", &move);
        switch (move){
        case 'w':
            move_up();
            break;
        case 'a':
            move_left();
            break;
        case 's':
            move_down();
            break;
        case 'd':
            move_right();
            break;
        default:
            printf("Invalid move. Try again.\n");
            continue;
        }
        if(win_check()){
            printf("YOU WIN!!!");
            break;
        }
        if(full_check()){
            printf("GAME OVER");
            break;
        }
        generate_number();   
    } 
    return 0;
}
