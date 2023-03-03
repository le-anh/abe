#include <chrono>
#include <cstdint>
#include <iostream>

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void setup()
{
    int iterator = 20;
	uint64_t time = 0;
	uint64_t start_time;
	uint64_t end_time;
	for(int i = 1; i <= iterator; i++)
	{
	    start_time = timeSinceEpochMillisec();
		system("cpabe-setup");
	    end_time = timeSinceEpochMillisec();

		time += timeSinceEpochMillisec() - start_time;
	}
	printf("Setup %0.3lf milliseconds (%0.3lf seconds).\n", (double)(time) / iterator, (double)(time) / (1000 * iterator));
}

void key_generation()
{
    int iterator = 20;
	uint64_t start_time;
	uint64_t end_time;
    for(int k = 1; k <= 4; k++)
    {
	    uint64_t time = 0;
        for(int i = 1; i <= iterator; i++)
        {
            start_time = timeSinceEpochMillisec();
            switch (k)
            {
                case 1:
                    system("cpabe-keygen -o priv_5 pub_key master_key attr1 attr2 attr3 attr4 attr5");
                    break;
                case 2:
                    system("cpabe-keygen -o priv_10 pub_key master_key attr1 attr2 attr3 attr4 attr5 attr6 attr7 attr8 attr9 attr10");
                    break;
                case 3:
                    system("cpabe-keygen -o priv_15 pub_key master_key attr1 attr2 attr3 attr4 attr5 attr6 attr7 attr8 attr9 attr10 attr11 attr12 attr13 attr14 attr15");
                    break;
                case 4:
                    system("cpabe-keygen -o priv_20 pub_key master_key attr1 attr2 attr3 attr4 attr5 attr6 attr7 attr8 attr9 attr10 attr11 attr12 attr13 attr14 attr15 attr16 attr17 attr18 attr19 attr20");
                    break;
                default:
                    break;
            }
            end_time = timeSinceEpochMillisec();

            time += timeSinceEpochMillisec() - start_time;
        }
        printf("Key generation %0.3lf milliseconds (%0.3lf seconds) with %d attributes.\n", (double)(time) / iterator, (double)(time) / (1000 * iterator), k*5);
    }
}

int main()
{
    setup();
    key_generation();
    return 0;
}