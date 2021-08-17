#include <stdio.h>
#include <stdlib.h>
#include "the3.h"

int my_strcmp(char*a,char*b){
  for(;*a==*b;a++,b++)
    if(*a=='\0') return 1;
  return 0;
}

Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth){
  Apartment *current_apartment=head,*new_apartment=(Apartment*)calloc(1,sizeof(Apartment));
  int i;

  new_apartment->name=apartment_name;
  new_apartment->max_bandwidth=max_bandwidth;

  if(head==NULL){
    new_apartment->next=new_apartment;
    return new_apartment;
  }

  if(index==0){
    for(;current_apartment->next!=head;current_apartment=current_apartment->next);
    new_apartment->next=current_apartment->next;
    current_apartment->next=new_apartment;
    return new_apartment;
  }

  for(i=1;i<index;i++)
    current_apartment=current_apartment->next;

  new_apartment->next=current_apartment->next;
  current_apartment->next=new_apartment;

  return head;
}

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth){
  Apartment *current_apartment=head;
  Flat *current_flat,*new_flat=(Flat*)calloc(1,sizeof(Flat));
  int current_bandwidth=0,i;

  new_flat->id=flat_id;
  new_flat->initial_bandwidth=initial_bandwidth;

  for(;!my_strcmp(current_apartment->name,apartment_name);current_apartment=current_apartment->next);
  
  for(current_flat=current_apartment->flat_list;current_flat;current_flat=current_flat->next)
    current_bandwidth+=current_flat->initial_bandwidth;
  
  if(current_bandwidth+initial_bandwidth>current_apartment->max_bandwidth)
    initial_bandwidth=current_apartment->max_bandwidth-current_bandwidth;
  
  new_flat->initial_bandwidth=initial_bandwidth;

  if(current_apartment->flat_list==NULL){
    current_apartment->flat_list=new_flat;
    return;
  }

  if(index==0){
    new_flat->next=current_apartment->flat_list;
    current_apartment->flat_list->prev=new_flat;
    current_apartment->flat_list=new_flat;
    return;
  }

  current_flat=current_apartment->flat_list;

  for(i=1;i<index;i++,current_flat=current_flat->next);

  new_flat->next=current_flat->next;

  if(new_flat->next) new_flat->next->prev=new_flat;

  new_flat->prev=current_flat;
  current_flat->next=new_flat;
}

Apartment* remove_apartment(Apartment* head, char* apartment_name){
  Apartment *current_apartment=head,*next;
  Flat *current_flat;
  char* name=head->name,no_apartments_left=0;

  for(;!my_strcmp(current_apartment->next->name,apartment_name);current_apartment=current_apartment->next);

  next=current_apartment->next;
  if(next==current_apartment) no_apartments_left=1;
  current_apartment->next=current_apartment->next->next;
  current_flat=next->flat_list;

  if(current_flat!=NULL){
    for(;current_flat->next!=NULL;current_flat=current_flat->next);
    for(;current_flat->prev!=NULL;current_flat=current_flat->prev)
      free(current_flat);
    free(current_flat);
  }
  free(next);

  if(no_apartments_left) return NULL;
  if(my_strcmp(name,apartment_name)) return current_apartment->next;
  else return head;
}

void make_flat_empty(Apartment* head, char* apartment_name, int flat_id){
  Apartment* current_apartment=head;
  Flat* current_flat=head->flat_list;

  while(current_flat==NULL){
      current_apartment=current_apartment->next;
      current_flat=current_apartment->flat_list;
  }

  while(1){
    while(current_flat==NULL){
      current_apartment=current_apartment->next;
      current_flat=current_apartment->flat_list;
    }
    if(flat_id==current_flat->id) break;
    current_flat=current_flat->next;
  }

  current_flat->initial_bandwidth=0;
  current_flat->is_empty=1;
}

int find_sum_of_max_bandwidths(Apartment* head){
  Apartment *current_apartment;
  int sum_of_max_bandwidths;
  if(head){
    current_apartment=head->next;
    sum_of_max_bandwidths=head->max_bandwidth;
  }
  else{
    return 0;
  }
  for(;current_apartment!=head;sum_of_max_bandwidths+=current_apartment->max_bandwidth,current_apartment=current_apartment->next);
  return sum_of_max_bandwidths;
}

Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2){
  Apartment *apartment1=head,*apartment2=head;
  Flat* current_flat=NULL;

  for(;!my_strcmp(apartment1->name,apartment_name_1);apartment1=apartment1->next);
  for(;!my_strcmp(apartment2->name,apartment_name_2);apartment2=apartment2->next);

  apartment1->max_bandwidth+=apartment2->max_bandwidth;

  if(apartment1->flat_list==NULL){
    apartment1->flat_list=apartment2->flat_list;
  }
  else{
    for(current_flat=apartment1->flat_list;current_flat->next;current_flat=current_flat->next);
    current_flat->next=apartment2->flat_list;
  }

  if(apartment2->flat_list) apartment2->flat_list->prev=current_flat;

  apartment2->flat_list=NULL;
  return remove_apartment(head,apartment_name_2);
}

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list){
  Apartment *current_apartment=head,*shifted_apartment=head;
  Flat *current_flat=current_apartment->flat_list,*shifted_flat=head->flat_list;

  while(1){
    if(shifted_flat==NULL){
      shifted_apartment=shifted_apartment->next;
      shifted_flat=shifted_apartment->flat_list;
    }
    else if(shifted_flat->id==flat_id_to_shift){
      break;
    }
    else{
      shifted_flat=shifted_flat->next;
    }
  }
  
  for(;*flat_id_list!=0;flat_id_list++){

    while(1){
      if(current_flat==NULL){
        current_apartment=current_apartment->next;
        current_flat=current_apartment->flat_list;
      }
      else if(current_flat->id==*flat_id_list){
        current_apartment->max_bandwidth-=current_flat->initial_bandwidth;
        shifted_apartment->max_bandwidth+=current_flat->initial_bandwidth;
        break;
      }
      else{
        current_flat=current_flat->next;
      }
    }

    if(current_flat->prev){
      current_flat->prev->next=current_flat->next;
    }
    else{
      current_apartment->flat_list=current_flat->next;
    }

    if(current_flat->next)
      current_flat->next->prev=current_flat->prev;

    if(shifted_flat->prev){
      current_flat->prev=shifted_flat->prev;
      shifted_flat->prev->next=current_flat;
    }
    else{
      shifted_apartment->flat_list=current_flat;
      current_flat->prev=NULL;
    }

    shifted_flat->prev=current_flat;
    current_flat->next=shifted_flat;
  }
}