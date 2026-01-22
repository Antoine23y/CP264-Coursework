/*
--------------------------------------------------
Project: a4q2
File:    myrecord.c
Author:  Antoine Youssef
Version: 2025-01-09
--------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"

int cmp1(void *x, void *y) {
	float scoreA = ((RECORD*) x)->score;
	float scoreB = ((RECORD*) y)->score;
	return (scoreB > scoreA) - (scoreB < scoreA); // Flip the comparison for descending order
}


/*
 * Define a structure named RECORD to hold a person's name of 20 characters and 
 * the score of float type.
*/

/*
 * Define a structure named STATS containing fields: int count, float mean, 
 * loat stddev (standard deviation), and float median.
*/

/*
 * Define a structure named GRADE to hold a string letter_grade at most 2 letters. 
*/

/*
 * Convert a percentage grade to letter grade defined by percentage ranges
 * A+=[90, 100], A=[85, 90), A-=[80, 85), B+=[77, 80), B=[73, 77) B-=[70, 73),
 * C+=[67, 70), C=[63, 77), C-=[60, 63), D+=[57,60),D=[53,57),D-=[50,53), F=[0,50).
 *
 * @param score -  percetage grade.
 *
 * @return - letter grade wrapped in GRADE structure type.
 */
GRADE grade(float score) {

    GRADE result;

    if (score >= 90) strcpy(result.letter_grade, "A+");
    else if (score >= 85) strcpy(result.letter_grade, "A");
    else if (score >= 80) strcpy(result.letter_grade, "A-");
    else if (score >= 77) strcpy(result.letter_grade, "B+");
    else if (score >= 73) strcpy(result.letter_grade, "B");
    else if (score >= 70) strcpy(result.letter_grade, "B-");
    else if (score >= 67) strcpy(result.letter_grade, "C+");
    else if (score >= 63) strcpy(result.letter_grade, "C");
    else if (score >= 60) strcpy(result.letter_grade, "C-");
    else if (score >= 57) strcpy(result.letter_grade, "D+");
    else if (score >= 53) strcpy(result.letter_grade, "D");
    else if (score >= 50) strcpy(result.letter_grade, "D-");
    else strcpy(result.letter_grade, "F");

    return result;
}

/*
 *  Import record data from file and store name and store all record entries
 *  in the RECORD array passed by records, return the number of record count.
 *
 *  @param *fp -  FILE pointer to intput file.
 *  @param dataset - array of RECODR type to store record data.
 *  @return   - number of records
 */
int import_data(FILE *fp, RECORD *dataset) {

    int count = 0;
    char line[101];

    while (fgets(line, sizeof(line), fp) != NULL) {

        sscanf(line, "%[^,], %f", dataset[count].name, &dataset[count].score);
        count ++;
    }
    return count;
}

/*
 *  Take the RECORD data array as input, compute the average score, standard deviation,
 *  median of the score values of the record data, and returns the STATS type value.
 *
 *  @param dataset -  input record data array.
 *  @param count -  the number of data record in dataset array.
 *  @return  -  stats value in STATS type.
 */
STATS process_data(RECORD *dataset, int count) {

    STATS s;
    
    float total = 0;

    for (int i = 0; dataset[i].score; i ++) {
        total += dataset[i].score;
    }
    
    float mean = total / count;

    float median = 0;

    if (count % 2 == 0) {
        median = (dataset[(count / 2) - 1].score + dataset[count / 2].score) / 2;
    }

    else {
        median = dataset[count / 2].score;
    }

    float std = 0;
    for (int i = 0; dataset[i].score; i ++) {
        float x = (dataset[i].score - mean);
        x = x * x;
        std += x;
    }

    std = sqrt(std / count);

    s.count = count;
    s.mean = mean;
    s.median = median;
    s.stddev = std;

    return s;
}

/*
 *  This function takes output file named outfilename, RECORD array records, 
 *  and stats as inputs, prepare and write report of stats and grade to files.
 *  The records in report file are sorted in decreasing of scores.  
 *
 *  @param *fp -  FILE pointer to output file.
 *  @param *dataset - pointer to dataset array.
 *  @param count - the number of data record in dataset array.
 *  @return - returns 1 if successful; 0 if count < 1
 */
int report_data(FILE *fp,  RECORD *dataset, STATS stats) {
    
    if (stats.count > 0) {
        fprintf(fp, "%s\n", "stats:value");
        fprintf(fp, "%s%d\n", "count:", stats.count);
        fprintf(fp, "%s%.1f\n", "mean:", stats.mean);
        fprintf(fp, "%s%.1f\n", "stddev:", stats.stddev);
        fprintf(fp, "%s%.1f\n\n", "median:", stats.median);

        fprintf(fp, "%s\n", "name:score,grade");

		void *p[stats.count];
		for (int i = 0; i < stats.count; i++) {
			p[i] = &dataset[i];

		}

		my_sort(p, 0, stats.count - 1, cmp1);

		for (int i = 0; i < stats.count; i++) {
			RECORD *rec = (RECORD*) p[i];
			GRADE g = grade(rec->score);
			fprintf(fp, "%s:%.1f,%s\n", rec->name, rec->score, g.letter_grade);

		}
		return 1;
    } 

    else {
        return 0;
    }
}

int cmp2(void *x, void *y) {
    float b = ((RECORD*) x)->score;
    float a = ((RECORD*) y)->score;
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
} 