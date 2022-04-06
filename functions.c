#include <stdlib.h>
#include <stdio.h>

#define n_sector 3


float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    float  ***sector_times;
    float temp;
    int i, j, k;

    scanf("%u", n_drivers);
    scanf("%u", n_laps);


    sector_times = (float ***) malloc(sizeof(float **) * (*n_drivers));

    for (i=0; i < *n_drivers; i++)
    {
        sector_times[i] = (float **) malloc(sizeof(float *) * (*n_laps));
    }

    for (i=0; i < *n_drivers; i++)
    {
        for (j=0; j < *n_laps; j++)
        {
            sector_times[i][j] = (float *) malloc(sizeof(float) * n_sector);
        }
    }

    for (i=0; i < *n_drivers ; i++)
    {
        for (j=0; j < *n_laps; j++)
        {
            for (k=0; k < n_sector; k++)
            {
                scanf(" %f", &temp);
                sector_times[i][j][k] = temp;         
            }
        }
    }

    return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){

    unsigned int ** positions, temp;
    
    int i, j;

    scanf("%u", p_drivers);
    scanf("%u", n_races);

    positions = (unsigned int **) malloc(sizeof(unsigned int *) * (*p_drivers));

    for (i=0; i < *p_drivers; i++)
    {
        positions[i] = (unsigned int *) malloc(sizeof(unsigned int) * (*n_races));
    }

    for (i=0; i< *p_drivers; i++)
    {
        for (j=0; j < *n_races; j++)
        {
            scanf(" %u", &temp);
            positions[i][j] = temp;
        }
    }

    return positions;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    float ** lap_times;
    int i, j, k;
    float sum = 0;

    lap_times = (float **) malloc(sizeof(float *) * n_drivers);

    for (i=0; i < n_drivers; i++)
    {
        lap_times[i] = (float *) malloc(sizeof(float) * n_laps);
    }

    for (i=0; i < n_drivers ; i++)
    {
        for (j=0; j < n_laps; j++)
        {
            for (k=0; k < n_sector; k++)
            {
                sum += sector_times[i][j][k];
            }

            lap_times[i][j] = sum;
            sum = 0;

        }
    }

    return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){

    int i, j;
    unsigned int fastest = 0;
    float fastest_time;

    fastest_time = lap_times[0][0];

    for (i=0; i < n_drivers; i++)
    {
        for (j = 0; j < n_laps; j++)
        {
            if ((fastest_time - lap_times[i][j]) > 0.0001){
                fastest_time = lap_times[i][j];
                fastest = i;
            }
        }
        
    }


    return fastest;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    int i, j;
    float lap_time = 0, temp_time = 0;
    unsigned int fastest_lap = 0;

    for (j=0; j < n_sector; j++)
    {
        lap_time += sector_times_of_driver[0][j]; 
    }        

    for (i=0; i < n_laps; i++)
    {
        for (j=0; j < n_sector; j++)
        {
            temp_time += sector_times_of_driver[i][j]; 
        }
        
        if ((lap_time - temp_time) > 0.0001)
        {
            lap_time = temp_time;
            fastest_lap = i;
        }
        temp_time = 0;
    }

    return fastest_lap;
}

float* selection_sort(float* arr, unsigned int len, char ord){
    float * sorted_arr, temp;
    int i, j, index;
    
    sorted_arr = (float *) malloc(sizeof(float) * len);

    for (i=0; i < len; i++) sorted_arr[i] = arr[i];

    if (ord == 'D')
    {
        for (i=0; i < len; i++)
        {
            index = i;
            temp = sorted_arr[i];
            for (j=i; j < len; j++)
            {
                if (sorted_arr[j] > temp )
                {
                    temp = sorted_arr[j];
                    index = j;
                }
            }
            if (i != index)
            {    
                sorted_arr[index] = sorted_arr[i];
                sorted_arr[i] = temp;
            }             
        }
    }
    else
    {
        for (i=0; i < len; i++)
        {
            index = i;
            temp = sorted_arr[i];
            for (j=i; j < len; j++)
            {
                if (sorted_arr[j] < temp )
                {
                    temp = sorted_arr[j];
                    index = j;
                }
            }
            if (i != index)
            {    
                sorted_arr[index] = sorted_arr[i];
                sorted_arr[i] = temp;
            }        
        }            
    }

    return sorted_arr;
}


unsigned int* find_finishing_positions_helper(float* times, unsigned int n_drivers){
    unsigned int *drivers_id; 
    int i, j, min_index, temp;
    float min;

    drivers_id = (unsigned int *) malloc(sizeof(int) * n_drivers);

    for(i=0; i < n_drivers; i++) drivers_id[i] = i;

    for (i=0; i < n_drivers; i++)
    {
        min_index = i;
        min = times[i];
        for (j=i; j < n_drivers; j++)
        {
            if ((times[j] - min) < -0.0001)
            {
                min = times[j];
                min_index = j;
                temp = drivers_id[j];
            }
            else if (((times[j] - min) <= 0.0001 && (times[j] - min) >= -0.0001) && (drivers_id[j] < drivers_id[min_index]))
            {
                min = times[j];
                min_index = j;
                temp = drivers_id[j];
            }            
        }

        
        
        if (i != min_index)
        {    
            times[min_index] = times[i];
            times[i] = min;
            drivers_id[min_index] = drivers_id[i];
            drivers_id[i] = temp;
        }
                   
    }    

    return drivers_id;
}



unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    float * times_sum, sum;
    int i, j;
    
    times_sum = (float *) malloc(sizeof(float) * n_drivers);

    for (i=0; i < n_drivers; i++)
    {
        sum = 0;
        for (j=0; j < n_laps; j++)
        {
            sum += lap_times[i][j];
        }
        times_sum[i] = sum;
    }

    return find_finishing_positions_helper(times_sum, n_drivers);
    
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){

    float * time_diff, dif = 0;
    int j;

    time_diff = (float *) malloc(sizeof(float) * n_laps);

    for (j=0; j < n_laps; j++)
    {
        dif += lap_times[driver1][j] - lap_times[driver2][j];
        time_diff[j] = dif;
    }

    return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){

    unsigned int * position_points, * total_points, sum;
    int i, j;

    position_points = (unsigned int *) malloc(sizeof(unsigned int) * p_drivers);
    total_points = (unsigned int *) malloc(sizeof(unsigned int) * p_drivers);

    for (i=0; i < p_drivers; i++) {scanf(" %u", position_points+i);}

    for (i = 0; i < p_drivers; i++)
    {
        sum = 0;
        for (j=0; j < n_races; j++)
        {
            sum += position_points[positions[i][j] - 1];
        }
        total_points[i] = sum;
    }

    return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    unsigned int season_rank = 1;
    int i;

    for (i=0; i < p_drivers; i++)
    {
        if (total_points[i] > total_points[id]) season_rank++;
        else if (total_points[i] == total_points[id] && i < id) season_rank++;
    }
    return season_rank;
}
