#include "functions.h"



int main(){
    int  i, j;
    unsigned int drivers,  laps, races, *r, *l, *d, *finishing_positions, 
    driver1 = 0, driver2 = 1, * total_points, ** positions, season_rank;
    float *** sector_times;
    float ** lap_times, * time_diff;
    

    /*scanf(" %u", &race);*/
    /*scanf(" %u", &drivers);
    scanf(" %u", &laps);*/

    /*r = &race;*/
    d = &drivers;
    l = &laps;
    r = &races;  
    
    sector_times = create_sector_times(d, l);

    lap_times = calculate_lap_times(sector_times, *d, *l);

    for (i=0; i < drivers ; i++)
    {
        for (j=0; j < laps ; j++)
        {
            printf("%.2f ", lap_times[i][j]);
        }
        printf("\n");
    }


    finishing_positions = find_finishing_positions(lap_times, drivers, laps);

    for (i = 0; i < drivers; i++)
    {
        printf("%d ", finishing_positions[i]);
    }
    printf("\n");

    time_diff = find_time_diff(lap_times, drivers, laps, driver1, driver2);

    for (i=0; i < laps; i++)
    {
        printf("%f ", time_diff[i]);
    }
    printf("\n");
    

    /*
    driver_sector_times = (float **) malloc(sizeof(float  *) * (*l));

    for (i=0; i < 3; i++)
    {
        driver_sector_times[i] = (float *) malloc(sizeof(float) * 3);
    }

    for (i = 0; i < *l; i++)
    {
        for (j = 0; j < 3; j++)
        {
            scanf("%f", &temp);
            driver_sector_times[i][j] = temp;
        }
        
    }
    



    driver_lap = find_driver_fastest_lap(driver_sector_times, 3);

    printf("Lap: %d\n", driver_lap);

    */

    /*
    for (i=0; i < drivers ; i++)
    {
        for (j=0; j < laps ; j++)
        {
            for (k=0; k < 3; k++)
            {
                printf(" %.2f", sector_times[i][j][k]);         
            }
        }
    }     
    */
    

    positions = create_positions(d, r);

    total_points = calculate_total_points(positions, drivers, races);

    for (i=0; i < drivers; i++)
    {
        printf("%u ", total_points[i]);
    }
    printf("\n");

    season_rank = find_season_ranking(total_points, drivers, 9);
    printf("%u\n", season_rank);

    return 0;
}
