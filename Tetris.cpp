#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// This function checks if the shape can fit in the given range of the row.
int CheckFit(vector<string>& shape, vector<string>& rows, int l, int r)
{
    for(int i = 0; i < shape.size(); i++)
    {
        int k = 0;
        for(int j = l; j < r; j++)
        {
            if(rows[i][j] == '*' && shape[i][k] == '*') 
            {
                return 0;  // If there's a collision, return 0.
            }
            if(rows[i][j] == '.' && shape[i][k] == '*') 
                rows[i][j] = '*';  // Place the shape.
            k++;
        }
    }

    int count = 0;
    for(const auto& row : rows)
    {    
        if(count(row.begin(), row.end(), '*') == row.length()) 
            count++;  // Count full cleared rows.
    }

    return count;
}

// This function checks if the vertical placement is valid (no conflicts in the columns above).
bool CheckVertical(const vector<string>& field, int index, int l, int r)
{
    for(int j = l; j < r; j++)
    {
        for(int i = index - 1; i >= 0; i--)
        {
            if(field[i][j] == '*') 
                return false;  // There's a block above.
        }
    }
    return true;
}

int main()
{
    int SH, SW, FH, FW;
    cin >> SW >> SH;

    vector<string> shape(SH), field;
    for(int i = 0; i < SH; i++) 
        cin >> shape[i];  // Read shape.

    cin >> FW >> FH;
    field.resize(FH);
    for(int i = 0; i < FH; i++) 
        cin >> field[i];  // Read field.

    int maxCleared = -1, X = 0, Y = 0;

    for(int i = FH - SH; i >= 0; i--)  // Iterate over the field.
    {
        int space_l = field[i].find('.'), 
            space_r = field[i].find_first_not_of('.', space_l + 1);

        if(space_r == -1) 
        {
            space_r = field[i].find_last_of('.') + 1;
        }

        if(space_r - space_l >= SW)  // Check if space is wide enough.
        {
            vector<string> lines(SH);
            for(int j = 0; j < SH; j++)
            {
                lines[j] = field[i + j];  // Extract the lines where the shape will be placed.
            }

            while(space_l < space_r) 
            {
                int cleared = CheckFit(shape, lines, space_l, space_r);            

                if(!CheckVertical(field, i, space_l, space_r))
                {
                    space_l++;
                    continue;
                }
                
                if(cleared > maxCleared)
                {
                    Y = FH - i - 1;  // Update Y-coordinate.
                    X = space_l;  // Update X-coordinate.
                    maxCleared = cleared;  // Update max cleared rows.
                }
                space_l++;
            }
        }
    }

    cout << X << ' ' << Y << endl << maxCleared << endl;  // Output the best placement and cleared rows.
}
