#include <stdio.h>
#include <malloc.h>

#define EDGE struct edge

EDGE{
    //structure of edge
    int start;
    int end;
    long long value;
};

void swap(EDGE *edges, int a, int b){
    //function to swap elements in array
    EDGE tmp = *(edges + a);
    *(edges + a) = *(edges + b);
    *(edges + b) = tmp;
}

int partition(EDGE *edges, int frst, int lst){
    //function to find pivot element
    EDGE pivot = *(edges + frst);
    int i = frst, j = lst;

    while (frst < lst){
        while ((*(edges + i)).value < pivot.value)
            i++;
        while ((*(edges + j)).value > pivot.value)
            j--;
        if (i < j)
            swap(edges, i++, j--);
        else
            return j;
    }
}

void qckSort(EDGE* edges, int frst, int lst){
    if (lst <= frst)
        return;
    int p = partition(edges, frst, lst);
    qckSort(edges, 0, p);
    qckSort(edges, p + 1, lst);
}

int check(int n, int m){
    //to check input data
    if (n < 0 || n > 5000){
        printf("bad number of vertices");
        return -1;
    }

    if (m < 0 || m > (n*(n+1))/2){
        printf("bad number of edges");
        return -1;
    }
    return 0;
}

void printRes(EDGE *res, int n){
    //to print the result
    for (int i = 0; i < n; ++i) {
        printf("%d %d\n", (*(res + i)).start + 1, (*(res + i)).end + 1);
    }
}

void prima(EDGE *edges, int *mst, int m, int n){
    EDGE *res;
    *(mst + 0) = 1;
    res = (EDGE *) malloc(sizeof (EDGE) * (n - 1));

    int numMST = 0; 
    int numEdges = 0;
    //already checked edges

    qckSort(edges, 0, m - 1);

    while (numMST < (n - 1) && numEdges < m){
        int flag1 = 0, flag2 = 0;
        int var1 = (*(edges + numEdges)).start;
        int var2 = (*(edges + numEdges)).end;

        if (*(mst + var1) == 1 && *(mst + var2) == 0)
            flag1 = 1;
        else if (*(mst + var2) == 1 && *(mst + var1) == 0)
            flag2 = 1;

        if (flag1 == 1){
            *(res + numMST++) = *(edges + numEdges);
            (*(edges + numEdges)).value = LLONG_MAX;
            *(mst + (*(edges + numEdges)).end) = 1;
            numEdges = 0;
            qckSort(edges, 0, m - 1);
        }

        else if (flag2 == 1){
            *(res + numMST++) = *(edges + numEdges);
            (*(edges + numEdges)).value = LLONG_MAX;
            *(mst + (*(edges + numEdges)).start) = 1;
            numEdges = 0;
            qckSort(edges, 0, m - 1);
        }
        else
            numEdges++;
    }

    if (numMST != (n - 1)){
        printf("no spanning tree");
        exit(0);
    }

    printRes(res, numMST);
    free(res);
}

int main(){
    EDGE *edges;
    int *mst;
    //array of vertices in MST
    int n, m, start, end, count = 0;
    long long value;

    scanf("%d", &n);
    scanf("%d", &m);

    if (n == 1){
        printf("");
        exit(0);
    }

    mst = (int*) malloc(sizeof (int) * n);
    edges = (EDGE *)malloc(sizeof (EDGE) * m);

    for (int i =  0; i < m; ++i) {
        if (scanf("%d %d %lld", &start, &end, &value) != 3){
            printf("bad number of lines");
            exit(0);
        }

        if (start < 1 || start > n || end < 1 || end > n){
            printf("bad vertex");
            exit(0);
        }

        if (value < 0 || value > INT_MAX){
            printf("bad length");
            exit(0);
        }

        if (start == n || end == n)
            count++;

        (*(edges + i)).start = start - 1;
        (*(edges + i)).end = end - 1;
        (*(edges + i)).value = value;
    }

    check(n, m);

    if (count == 0){
        printf("no spanning tree");
        exit(0);
    }

    for (int i = 0; i < n; ++i)
        *(mst + i) = 0;

    prima(edges, mst, m, n);
    free(edges);
    free(mst);

    return 0;
}
