#include"Graph.h"

int matrix[25][25], visited_cities[10], limit, cost = 0;

struct Graph
{
    struct Node* head; // ###only head - we will add all nodes by order.
    struct Edge* start;
};

struct Node
{
    int src;
    struct Node* next;
};

struct Edge {
    int src, dest, weight;
    struct Edge* next;
};

int tsp(int c)
{
 int count, nearest_city = 999;
 int minimum = 999, temp;
 for(count = 0; count < limit; count++)
 {
 if((matrix[c][count] != 0) && (visited_cities[count] == 0))
 {
 if(matrix[c][count] < minimum)
 {
 minimum = matrix[count][0] + matrix[c][count];
 }
 temp = matrix[c][count];
 nearest_city = count;
 }
 }
 if(minimum != 999)
 {
 cost = cost + temp;
 }
 return nearest_city;
}
 
void minimum_cost(int city)
{
 int nearest_city;
 visited_cities[city] = 1;
 printf("%d ", city + 1);
 nearest_city = tsp(city);
 if(nearest_city == 999)
 {
 nearest_city = 0;
 printf("%d", nearest_city + 1);
 cost = cost + matrix[city][nearest_city];
 return;
 }
 minimum_cost(nearest_city);
}

int dijsktra(struct Graph* head, struct Node* src, struct Node* tar, int numOfNodes)
{
    struct Edge* temp = head->start;
    int i, j, n, source, target, visited[10] = { 0 }, min = 999;
    int dist[10] = { 0 };
    int pre[10] = { 0 };
    int start, m, d, path[10];
    int cost[10][10] = { 0 }; //need to alloc precise number;
    n = numOfNodes;
    source = src->src;
    target = tar->src;
    
    // Input graph
    while (temp->next != NULL)
    {
        cost[head->start->src][head->start->dest] = head->start->weight;
        temp = temp->next;
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (cost[i][j] == 0)
                cost[i][j] = 999;
        }
    }
    // logic for dijkstra's aglorithm
    start = source;
    for (i = 1; i <= n; i++)
    {
        dist[i] = 999;  // here we initialize all distances with the maximum value (999) you take any other value also
        pre[i] = -1;   // pre for the previous node 
    }
    visited[source] = 1; // visited source node
    dist[source] = 0;  // distance of first node from first node is 0
    while (visited[target] == 0)
    {
        min = 999;
        m = 0;
        for (i = 1; i <= n; i++)
        {
            d = dist[start] + cost[start][i];   // calcualte the distance from the source
            if (d < dist[i] && visited[i] == 0)
            {
                dist[i] = d;
                pre[i] = start;
            }
            if (min > dist[i] && visited[i] == 0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        visited[m] = 1;
    }
    // logic for printing path
    start = target;
    j = 0;
    while (start != -1)
    {
        path[j++] = start;
        start = pre[start];
    }
    // printing of the path
    for (i = j - 1; i >= 0; i--)
    {
        if (i != j - 1)
            printf(" to ");
        printf("%d", path[i]);
    }

    printf("\n shortest path is %d", dist[target]);
    return 0;
}

char* str_slice(char str[], int slice_from, int slice_to)
{
    // if a string is empty, returns nothing
    if (str[0] == '\0')
        return NULL;

    char* buffer;
    size_t str_len, buffer_len;

    // for negative indexes "slice_from" must be less "slice_to"
    if (slice_to < 0 && slice_from < slice_to) {
        str_len = strlen(str);

        // if "slice_to" goes beyond permissible limits
        if (abs(slice_to) > str_len - 1)
            return NULL;

        // if "slice_from" goes beyond permissible limits
        if (abs(slice_from) > str_len)
            slice_from = (-1) * str_len;

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);

        // for positive indexes "slice_from" must be more "slice_to"
    }
    else if (slice_from >= 0 && slice_to > slice_from) {
        str_len = strlen(str);

        // if "slice_from" goes beyond permissible limits
        if (slice_from > str_len - 1)
            return NULL;

        buffer_len = slice_to - slice_from;
        str += slice_from;

        // otherwise, returns NULL
    }
    else
        return NULL;

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);
    return buffer;
}

char* readinput(int* len)
{
    int flag = 1;
    char* input = NULL;
    char tempbuf[200];
    size_t inputlen = 0, templen = 0;
    do {
        fgets(tempbuf, 200, stdin);
        templen = strlen(tempbuf);
        //input = (char*)malloc((templen+1)*sizeof(char));
        input = (char*)realloc(input, templen + 1);
        strcpy(input, tempbuf);
        //strncat(input, tempbuf, templen);
        //inputlen += templen;
        //tempbuf[200 - 2] = '\n';
        flag = 0;
    } while (flag);
    //printf("%d,%d", *len, templen);
    *len = (int)templen;
    return input;
}

void createHead(struct Graph* head, int src)
{
    struct Node* head1 = (struct Node*)malloc(sizeof(struct Node));
    head1->src = src;
    head1->next = NULL;
    head->head = head1;
}

void createNode(struct Node* head, int src)
{
    struct Node* temp = head;
    struct Node* toAdd = (struct Node*)malloc(sizeof(struct Node));
 
    toAdd->src = src;
    toAdd->next = NULL;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = toAdd;
}

void updateNode(struct Node* head, int srcToUpdate)
{
    struct Node* temp = head;
        while (temp->next != NULL && temp->src != srcToUpdate)
        {
            temp = temp->next;
        }

        if (temp->next != NULL)
        {
            temp->src = srcToUpdate;
        }
}

void removeNode(struct Node* head, int toDelete)
{
    struct Node* temp = head;
    struct Node* Delete;

    if (head->src != toDelete)
    {
        while (temp->next != NULL && temp->next->src != toDelete)
        {
            temp = temp->next;
        }
        Delete = temp->next;
        temp->next = temp->next->next;

        free(Delete); //free Memory of node to delete
    }
    else
    {
        Delete = head;
        head = head->next;
        free(Delete);
    }
}

int isNodeExist(struct Node* head, int isExist)
{
    struct Node* temp = head;
    int flag = 0;
    
    if (temp->src != isExist)
    {
        while (temp->next != NULL && temp->next->src != isExist)
        {
            temp = temp->next;
        }

        if (temp->next != NULL)
        {
            flag = 1;
        }
    }
    else
    {
        flag = 1;
    }
    
    return flag;
}

void createEdge(struct Edge* start, int src, int dest, int weight)
{
    struct Edge* temp = start;
    struct Edge* toAdd = (struct Edge*)malloc(sizeof(struct Edge));

    toAdd->src = src;
    toAdd->dest = dest;
    toAdd->weight = weight;
    toAdd->next = NULL;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = toAdd;
}

void createStart(struct Graph* start, int src, int dest, int weight)
{
    struct Edge* start1 = (struct Edge*)malloc(sizeof(struct Edge));

    start1->src = src;
    start1->dest = dest;
    start1->weight = weight;
    start1->next = NULL;

    start->start = start1;
}

void updateEdge(struct Edge* head, int src)
{
    if (head != NULL)
    {
        struct Edge* temp = head;
        while (temp->next != NULL)
        {
            if (temp->src == src)
            {
                removeEdge(head, temp->src);
            }
            temp = temp->next;
        }
    }
}

void removeEdge(struct Edge* head, int src)
{
    struct Edge* temp = head;
    struct Edge* toDelete = NULL;

    if (temp->src != src)
    {
        while (temp->next != NULL)
        {
            if (temp->next->src == src)
            {
                toDelete = temp->next;
                temp->next = temp->next->next;

                free(toDelete); //free Memory of node to delete
                break;
            }
            temp = temp->next;
        }
    }
    else
    {
        toDelete = head;
        head = head->next;
        free(toDelete);
    }
 }

int isEdgeExist(struct Edge* head, int src)
{
    struct Edge* temp = head;
    int flag = 0;
    if (temp->src != src)
    {
        while (temp->next != NULL && temp->next->src != src)
        {
            temp = temp->next;
        }

        if (temp->next != NULL)
        {
            flag = 1;
        }
    }
    else
    {
        flag = 1;
    }
   
    return flag;
}

void deleteGraph(struct Graph* g)
{
    struct Node* temp1 = g->head;
    struct Node* delete1;
    struct Edge* temp2 = g->start;
    struct Edge* delete2;

    while (temp1->next != NULL)
    {
        delete1 = temp1;
        temp1 = temp1->next;
        free(delete1);
    }
    free(temp1);

    while (temp2->next != NULL)
    {
        delete2 = temp2;
        temp2 = temp2->next;
        free(delete2);
    }
    free(temp2);

    g->head = NULL;
    g->start = NULL;
}

struct Graph* createGraph(char* input, int strlen)
{ 
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->head = NULL;
    graph->start = NULL;
    int numOfNodes = input[0];
    int flag = 0;
    int curNode = 0;
    int newNodes = 0;
    int i = 0;

    for  (i = 2; i < strlen; i+=2)
    {
        if (input[i] == 'n')
        {
            i += 2;
            curNode = input[i];
            if (graph->head == NULL)
            {
                createHead(graph, curNode);
                newNodes++;
            }
            else
            {
                if (isNodeExist(graph->head, curNode))
                {
                    createNode(graph->head, curNode);
                    newNodes++;
                }
            }
        }
        else
        {
            if (!isNodeExist(graph->head, input[i]))
            {
                createNode(graph->head, input[i]);
                newNodes++;
            }
            if (graph->start == NULL)
            {
                createStart(graph, curNode, input[i], input[i + 2]);
            }
            else
            {
                createEdge(graph, curNode, input[i], input[i + 2]);
            }
            //if node dosent exist create it
            i = i + 2;
        }

        if (input[i + 2] == 'B' || input[i + 2] == 'A' || input[i + 2] == 'D' || input[i + 2] == 'S' || input[i + 2] == 'T')
        {
            break;
        }
    }

    //test
    if (newNodes == numOfNodes)
    {
        printf("A - OK nodes");
    }
    input = str_slice(input, i, strlen + 1);
    return graph;
}

int getD(char input[], struct Graph* g)
{
    int toD = input[3];
    struct Edge* temp = g->start;
    struct Edge* toDelete = NULL;

    removeNode(g->head, toD);
    removeEdge(g->start, toD);

    if (temp->src != toD)
    {
        while (temp->next != NULL)
        {
            if (temp->next->dest == toD)
            {
                toDelete = temp->next;
                temp->next = temp->next->next;

                free(toDelete); //free Memory of node to delete
                break;
            }
            temp = temp->next;
        }
    }
    else
    {
        toDelete = g->start;
        g->start = g->start->next;
        free(toDelete);
    }

    input = str_slice(input, 6, strlen(input) + 1);

    return 0;
}

int getB(char input[], struct Graph* g)
{
    int flag = 0;
    int curNode = input[3];
    //int newNodes = 0;
    int i = 0;

    if (isNodeExist(g->head, input[3]))
    {
        updateEdge(g->start, curNode);
        //create edge  
    }
    else
    {
        createNode(g->head, input[3]);
    }

    for (i = 5; i < strlen(input); i += 2)
    {
        
        if (g->start == NULL)
        {
            createStart(g, curNode, input[i], input[i + 2]);
            i = i + 2;
        }
        else
        {
            createEdge(g, curNode, input[i], input[i + 2]);
            i = i + 2;
        }

        if (input[i + 2] == 'B' || input[i + 2] == 'A' || input[i + 2] == 'D' || input[i + 2] == 'S' || input[i + 2] == 'T')
        {
            break;
        }
    }

    input = str_slice(input, i, strlen(input) + 1);
    return 0;
}

int getS(char s[], struct Graph* g, int numOfNodes)
{
    int src = s[3];
    int dst = s[5];
    struct Node* Nsrc = g->start;
    struct Node* Ndst = g->start;

    while (Nsrc->next != NULL)
    {
        if (Nsrc->src != src)
        {
            Nsrc = Nsrc->next;
        }
    }

    while (Ndst->next != NULL)
    {
        if (Ndst->src != dst)
        {
            Nsrc = Nsrc->next;
        }
    }

    dijsktra(g, Nsrc, Ndst, numOfNodes);
   s= str_slice(s, 6, strlen(s) + 1);

    return 0;
}

int getT(char input[], struct Graph* g, int numOfNodes)
{
    int i, j = 0;    

   limit = input[2];

    printf("\n\nPath:\t");
    minimum_cost(0);
    printf("\n\nMinimum Cost: \t");
    printf("%d\n", cost);

    input = str_slice(input, 6, strlen(input) + 1);

    return 0;
}

void OptionManager(char choise, char input[], int lenStr)
{
    struct Graph* graph = NULL;
    int flag = 1;
    int numOfNodes = 0;
    while (flag)
    {
        switch (choise)
        {
        case 'A':
            if (graph != NULL)
            {
                deleteGraph(graph);
            } 
            numOfNodes = input[3];
            graph = createGraph(input, lenStr);
            break;
        case 'B':
            getB(input, graph);
            break;
        case 'D':
            getD(input, graph);
            break;
        case 'S':
            getS(input, graph, numOfNodes);
            break;
        case 'T':
            printf("still on work");
            break;
        default:
            flag = 0;
            break;
        }

        choise = input[0];
    }

}


// Weighted Directed graph implementation in C

int main(void)
{
    int lenStream = 0;
    char* stream = readinput(&lenStream);

    OptionManager(stream[0], str_slice(stream, 2, lenStream+1), lenStream-2);

    free(stream);

    return 0;
}