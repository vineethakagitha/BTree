#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
void read(FILE *fp);
void findRecord();
int findRecordrec(FILE *fp, int id);

struct student
{
	int id;
	char students[28];
	char college[28];
	int type;
};
struct nonleaf
{
	int offset[3];
	int key[2];
	char unused[40];
	int type;
};

void construct_tree(int *arr, FILE *fp);
int main()
{
	FILE *fp1;
	FILE *fp = fopen("dataInput.txt", "r");
	fp1 = fopen("StudentRecords.bin", "rb");
	if (!fp1)
	{
		read(fp);
	}
	else{
		char g[10], w[90], ch;
		int t;
		findRecord();
		fclose(fp);
	}
	_getch();
}

void read(FILE *fp)
{
	printf("fghjk");
	struct student st, ch;
	int c = 0;
	char cha[100], v, i = 0;
	FILE *fp1 = fopen("StudentRecords.bin", "wb");
	int arr[1000];
	memset(&st, '\0', sizeof(struct student));
	while (!feof(fp))
	{
		fscanf(fp, "%d,%[^,],%[^\n]", &st.id, &st.students, &st.college);
		arr[i++] = st.id;
		printf("%d %s\n %s\n", st.id, st.students, st.college);
		fwrite(&st, sizeof(struct student), 1, fp1);
	}
	construct_tree(arr, fp1);
	fclose(fp1);
}

void construct_tree(int *arr, FILE *fp)
{
	printf("\nfghjk");

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp) / 64;
	printf("\n%d", size);
	int arrindex = 1, arrprev = 1;
	int count = size, offset = 0;
	struct nonleaf st;
	memset(&st, '\0', sizeof(struct student));
	printf("\n%d\n", arr[0]);
	while (count != 0)
	{
		printf("\n%d\n", arr[1]);
		for (int j = 0; j < count / 3; j++)
		{
			for (int i = 0; i < 3; i++)
				st.offset[i] = offset++;
			st.type = 1;
			st.key[0] = arr[arrindex++];
			st.key[1] = arr[arrindex++];
			arr[arrprev++] = arr[arrindex++];
			printf("%d %d\n", st.key[0], st.key[1]);
			fwrite(&st, sizeof(struct student), 1, fp);
		}
		printf("\n");
		arrindex = 1;
		arrprev = 1;
		count = count / 3;
	}
}

void findRecord()
{
	FILE *fp;
	struct nonleaf lp;
	struct student st;
	int id, rec;
	printf("Enter id to search: ");
	scanf("%d", &id);
	fp = fopen("StudentRecords.bin", "rb+");
	printf("%d", ftell(fp));

	fseek(fp, -64, SEEK_END);
	findRecordrec(fp, id);
	/*if(findRecordrec(fp,id))
	       printf("Records are: %s %s", st.college, st.students);
			else
				printf("Sorry no Record Found");
			return;*/
	fclose(fp);
}
int findRecordrec(FILE *fp ,int id){

	struct nonleaf lp;
	struct student st;
	fread(&lp, sizeof(struct nonleaf), 1, fp);
	if (lp.type)
	{
		if (lp.key[0] > id)
		{
			fseek(fp, 64 * lp.offset[0], SEEK_SET);
			findRecordrec(fp, id);
		}
		else if (lp.key[1] < 0)
		{
			fseek(fp, 64 * lp.offset[1], SEEK_SET);
			findRecordrec(fp, id);
		}
		else{
			fseek(fp, 64 * lp.offset[2], SEEK_SET);
			findRecordrec(fp, id);
		}
	}
	else{
		fseek(fp, -64, SEEK_CUR);
		fread(&st, sizeof(struct student), 1, fp);
		if (st.id == id)
			printf("Records are: %s %s", st.college, st.students);
		else
			printf("Sorry no Record Found");
		return 0;

	}
}