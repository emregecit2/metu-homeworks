#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* Fill in the functions and define helper functions if you need to */


float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    int i,j,k;
    float ***sector_times;
    scanf("%u%u",n_drivers,n_laps);
    sector_times=(float***)malloc(sizeof(float**)**n_drivers);
    for(i=0;i<*n_drivers;i++){
        sector_times[i]=(float**)malloc(sizeof(float*)**n_laps);
        for(j=0;j<*n_laps;j++){
            sector_times[i][j]=(float*)malloc(sizeof(float)*n_sector);
            for(k=0;k<n_sector;k++)
                scanf("%f",sector_times[i][j]+k);
        }
    }
    return sector_times;
}

unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    unsigned int **sector_times;
    int driver,lap;
    scanf("%u%u",p_drivers,n_races);
    sector_times=(unsigned int**)malloc(sizeof(unsigned int*)**p_drivers);
    for(driver=0;driver<*p_drivers;driver++){
        sector_times[driver]=(unsigned int*)malloc(sizeof(unsigned int)**n_races);
        for(lap=0;lap<*n_races;lap++)
            scanf("%u",sector_times[driver]+lap);
    }
    return sector_times;
}

float* calculate_driver_lap_times(float **sector_times_of_driver,unsigned int n_laps){
    int lap,sector;
    float *lap_times;
    lap_times=(float*)calloc(n_laps,sizeof(float));
    for(lap=0;lap<n_laps;lap++){
        for(sector=0;sector<n_sector;sector++)
            lap_times[lap]+=sector_times_of_driver[lap][sector];
    }
    return lap_times;
}

float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    int driver;
    float **lap_times;
    lap_times=(float**)malloc(sizeof(float*)*n_drivers);
    for(driver=0;driver<n_drivers;driver++){
        lap_times[driver]=calculate_driver_lap_times(sector_times[driver],n_laps);
    }
    return lap_times;
}

unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    float fastest_lap=lap_times[0][0];
    int driver,lap;
    unsigned int id=0;
    for(driver=0;driver<n_drivers;driver++){
        for(lap=0;lap<n_laps;lap++)
            if(fastest_lap-lap_times[driver][lap]>0.0001){
                fastest_lap=lap_times[driver][lap];
                id=driver;
            }
    }
    return id;
}

unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    int lap,lap_number=0;
    float *lap_times=calculate_driver_lap_times(sector_times_of_driver,n_laps);
    for(lap=0;lap<n_laps;lap++){
        if(lap_times[lap_number]-lap_times[lap]>0.0001){
            lap_number=lap;
        }
    }
    return lap_number;
}

void sortA(float* arr, unsigned int len){
    int i,m=0;
    float ft=arr[0];
    if(len==1){
        return;
    }
    for(i=1;i<len;i++){
        if(arr[i]<arr[m]){
            m=i;
        }
    }
    arr[0]=arr[m];
    arr[m]=ft;
    sortA(arr+1,len-1);
}

void sortD(float* arr, unsigned int len){
    int i,m=0;
    float ft=arr[0];
    if(len==1){
        return;
    }
    for(i=1;i<len;i++){
        if(arr[i]>arr[m]){
            m=i;
        }
    }
    arr[0]=arr[m];
    arr[m]=ft;
    sortD(arr+1,len-1);
}

float* selection_sort(float* arr, unsigned int len, char ord){
    int i;
    float *arrcopy;
    arrcopy=(float*)malloc(sizeof(float)*len);
    for(i=0;i<len;i++){
        arrcopy[i]=arr[i];
    }
    switch(ord){
        case 'A':
            sortA(arrcopy,len);
            break;
        case 'D':
            sortD(arrcopy,len);
    }
    return arrcopy;
}
float my_abs(float i){
    return i<0?-i:i;
    }

void my_sortA(float* arr, unsigned int len, unsigned int* ids){
    int i,m=0,it=ids[0];
    float ft=arr[0];
    if(len==1){
        return;
    }
    for(i=1;i<len;i++){
        if(my_abs(arr[i]-arr[m])<0.0001){if(ids[i]<ids[m]) m=i;}
        else if(arr[i]<arr[m]) m=i;
    }
    arr[0]=arr[m];
    arr[m]=ft;
    ids[0]=ids[m];
    ids[m]=it;
    my_sortA(arr+1,len-1,ids+1);
}

float* calculate_total_times(float **lap_times,unsigned int n_laps,unsigned int n_drivers){
    int driver,lap;
    float *times;
    times=(float*)calloc(n_drivers,sizeof(float));
    for(driver=0;driver<n_drivers;driver++){
        for(lap=0;lap<n_laps;lap++){
            times[driver]+=lap_times[driver][lap];
        }
    }
    return times;
}

unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    unsigned int* ids,id;
    float *times;
    ids=(unsigned int*)malloc(sizeof(unsigned int)*n_drivers);
    for(id=0;id<n_drivers;id++){
        ids[id]=id;
    }
    times=calculate_total_times(lap_times,n_laps,n_drivers);
    my_sortA(times,n_drivers,ids);
    return ids;
}

float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1, unsigned int driver2){
    float* times,x;
    int lap;
    times=(float*)malloc(sizeof(float)*n_laps);
    x=0;
    for(lap=0;lap<n_laps;lap++){
        times[lap]=x;
        times[lap]+=lap_times[driver1][lap]-lap_times[driver2][lap];
        x=times[lap];
    }
    return times;
}

unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    int *position_point,race,driver;
    unsigned int *points;
    points=(unsigned int*)calloc(p_drivers,sizeof(unsigned int));
    position_point=(int*)malloc(sizeof(int)*p_drivers);
    for(driver=0;driver<p_drivers;driver++){
        scanf("%d",position_point+driver);
    }
    for(driver=0;driver<p_drivers;driver++){
        for(race=0;race<n_races;race++){
            points[driver]+=position_point[positions[driver][race]-1];
        }
    }
    return points;
}

unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    int driver,ranking=1;
    for(driver=0;driver<p_drivers;driver++){
        if(total_points[driver]>total_points[id]){
            ranking+=1;
        }
        else if(total_points[driver]==total_points[id]){
            if(driver<id){
                ranking+=1;
            }
        }
    }
    return ranking;
}