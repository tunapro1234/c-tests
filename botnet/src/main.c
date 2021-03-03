#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float getVirusCountByTime(float existingVirus, float ipm, float time);

int main(int argc, char** argv) {
	if (argc == 3) {
		float existingVirus = (float)strtod(argv[1], NULL);
		float ipm = (float)strtod(argv[2], NULL);

		for (int i = 1; i < 11; i++)
			printf("%d. dakika: %f\n", i, existingVirus = (existingVirus * (ipm + 1)));
	}

	else if (argc == 4) {
		float existingVirus = (float)strtod(argv[1], NULL);
		float ipm = (float)strtod(argv[2], NULL);
		float time = (float)strtod(argv[3], NULL);

		// printf("%d. dakika: %f\n", t, (float)pow((ipm + 1), (t)) * existingVirus);
		printf("%s. dakika: %f\n", argv[3], getVirusCountByTime(existingVirus, ipm, time));
		return 0;
	}

	else {
		printf("Usage: %s, [existing virus count], [infection per minute], [time](optional)\n", argv[0]);
		return 1;
	}
}

float getVirusCountByTime(float existingVirus, float ipm, float time) {
	return pow((ipm + 1), (time)) * existingVirus;
}