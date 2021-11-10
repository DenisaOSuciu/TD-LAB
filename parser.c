#include <stdio.h>
#include "parser.h"
    
STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t char_crt){
    static uint8_t s=0;
  switch (s)
    {
    case 0:{
        if(char_crt==13){
            s=1;
            date.line_count=0;
            return STATE_MACHINE_NOT_READY;
        }
        else {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
       case 1:{
       if(char_crt==10){
            s=2;
            return STATE_MACHINE_NOT_READY;
        }
        else {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
       
       }
       case 2:{
       if(char_crt=='O'){
            s=3;
            return STATE_MACHINE_NOT_READY;
        }
        else if(char_crt=='E'){
            s=12;
            return STATE_MACHINE_NOT_READY;
           
        }
        else if(char_crt=='+'){
            s=7;
            return STATE_MACHINE_NOT_READY;}

        else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
        
       }
        case 3:{
        if(char_crt=='K'){
            s=4;
            return STATE_MACHINE_NOT_READY;
        }
        else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
     }
    
    case 4:{
        if(char_crt==13){
            s=5;
            return STATE_MACHINE_NOT_READY;
        }
        else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }

       }
       
       case 5:{
       if(char_crt==10){
            s=6;
            return STATE_MACHINE_READY_OK;
        }
        else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
      }
       
    
    case 6:
    {
        date.status=1;
        return STATE_MACHINE_READY_OK;
        break;
    }

    case 7:
    {
        if(char_crt >=32 && char_crt<=126)
        {
            if(date.line_count<=AT_COMMAND_MAX_LINES && date.col_count<=AT_COMMAND_MAX_LINE_SIZE){
            date.data[date.line_count][date.col_count]=char_crt;}
            date.col_count++; 
            s=7;
            return STATE_MACHINE_NOT_READY;
        }
        else if(char_crt==13){
            if(date.line_count<=AT_COMMAND_MAX_LINES && date.col_count<=AT_COMMAND_MAX_LINE_SIZE)
            date.data[date.line_count][date.col_count]='\0';
            s=8;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }

    case 8:{
        if(char_crt==10){
            s=9;
            return STATE_MACHINE_NOT_READY;
        }
        else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }

    case 9:
    {
         
       if(char_crt=='+' && date.line_count<=AT_COMMAND_MAX_LINES){
           date.line_count++;
            date.col_count=0;
            s=7;
            return STATE_MACHINE_NOT_READY;

        }
        else if(char_crt==13){
            s=10;
            
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }

    case 10:{
        if(char_crt==10){
            s=11;
            return STATE_MACHINE_NOT_READY;

        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }

    case 11:
    {
        if(char_crt=='O'){
            s=3;
            return STATE_MACHINE_NOT_READY;
        }
        else if(char_crt=='E'){
            s=12;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 12:{
        if(char_crt=='R'){
            s=13;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 13:{
        if(char_crt=='R'){
            s=14;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 14:{
        if(char_crt=='O'){
            s=15;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 15:{
        if(char_crt=='R'){
            s=16;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }

    case 16:{
        if(char_crt==13){
            s=17;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 17:{
        if(char_crt==10){
            s=18;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 18:{
        date.status=0;
       return STATE_MACHINE_READY_OK;
       break;
    }
    default:
    break;

}

}

void afisare(){
    for(int i=0;i<=date.line_count;i++){
        int j=0;
        while(date.data[i][j]!='\0'){
            printf("%c", date.data[i][j]);
            j++;
        }
        printf("\n");
    }
}

void parcurgere(FILE *fisier){
    STATE_MACHINE_RETURN_VALUE value;
    char buff;
    do
    {   buff=fgetc(fisier);
        value=at_command_parse(buff);
    } while(buff != EOF);
  
    if(value == STATE_MACHINE_READY_OK){
            printf("STATE_MACHINE_READY_OK\n");
            printf("Finished with status: %d (1-OK, 0-ERROR)", date.status);
        }
        
        if(value == STATE_MACHINE_READY_WITH_ERROR){
            printf("STATE_MACHINE_READY_WITH_ERROR\n");
            
        }
}

int main(){
 
    FILE *fisier = fopen("test_file_copn_ok.txt","rb");
   
    if(fisier == NULL){
        printf("Eroare la deschiderea fisierului");
        return -1;
    }
    
    parcurgere(fisier);
    printf("\n\n");
    afisare();
    return 0;

    
}
