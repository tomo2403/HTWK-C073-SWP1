#include <iostream>
#include <sstream>

double parseFactor(std::istringstream &iss);

double parseTerm(std::istringstream &iss);

/**
 * @brief Parses and evaluates a factor in a mathematical expression.
 *
 * This function processes a factor, which can either be a number or a sub-expression
 * enclosed in parentheses. It supports multiplication and division operations.
 * If parentheses are encountered, the function recursively evaluates the expression
 * within them. Division by zero results in an error message and program termination.
 *
 * @param iss A reference to the input string stream containing the mathematical expression.
 * @return double The evaluated result of the factor.
 */
double parseFactor(std::istringstream &iss)
{
    // Skip whitespace characters
    while (iss.peek() == ' ') iss.get();

    // Check if the factor starts with an opening parenthesis
    if (iss.peek() == '(')
    {
        iss.get(); // Consume the '(' character
        const double value = parseTerm(iss); // Recursively evaluate the term within parentheses

        // Skip whitespace characters
        while (iss.peek() == ' ') iss.get();

        // Ensure the closing parenthesis is present
        if (iss.get() != ')')
        {
            std::cerr << "Fehlende schließende Klammer!" << std::endl;
            exit(1); // Terminate the program if a closing parenthesis is missing
        }
        return value; // Return the evaluated value of the sub-expression
    }
    else
    {
        double value;
        iss >> value; // Read the numeric value of the factor
        while (iss)
        {
            // Skip whitespace characters
            while (iss.peek() == ' ') iss.get();

            // Check for multiplication or division operators
            if (const char op = iss.peek(); op == '*' || op == '/')
            {
                iss.get(); // Consume the operator
                const double next = parseFactor(iss); // Recursively parse the next factor
                if (op == '*') value *= next; // Perform multiplication
                else
                {
                    if (next == 0) // Check for division by zero
                    {
                        std::cerr << "Division durch Null!" << std::endl;
                        exit(1); // Terminate the program on division by zero
                    }
                    value /= next; // Perform division
                }
            }
            else break; // Exit the loop if no '*' or '/' operator is found
        }
        return value; // Return the evaluated result of the factor
    }
}

/**
 * @brief Parses and evaluates a term consisting of factors connected by '+' or '-' operators.
 *
 * This function processes a term by first parsing a factor using `parseFactor` and then
 * iteratively checking for '+' or '-' operators to combine subsequent factors into the result.
 * It stops parsing when no more '+' or '-' operators are found in the input stream.
 *
 * @param iss A reference to the input string stream containing the mathematical expression.
 * @return double The evaluated result of the term.
 */
double parseTerm(std::istringstream &iss)
{
    // Parse the first factor in the term
    double value = parseFactor(iss);

    // Process subsequent factors connected by '+' or '-' operators
    while (iss)
    {
        // Peek at the next character to check for '+' or '-' operators
        if (const char op = iss.peek(); op == '+' || op == '-')
        {
            iss.get(); // Consume the operator
            const double next = parseFactor(iss); // Parse the next factor
            if (op == '+') value += next; // Add the factor if operator is '+'
            else value -= next; // Subtract the factor if operator is '-'
        }
        else break; // Exit the loop if no '+' or '-' operator is found
    }
    return value; // Return the evaluated result of the term
}

/**
 * @brief Main function to parse and evaluate a mathematical expression entered by the user.
 *
 * The program prompts the user to input a mathematical expression (e.g., "3 + 4 * 2 - 1"),
 * parses the input, and evaluates the result using helper functions `parseTerm` and `parseFactor`.
 * It supports basic arithmetic operations: addition, subtraction, multiplication, and division.
 *
 * @return int Returns 0 upon successful execution.
 */
int main()
{
    // Variable to store the user's input expression
    std::string input;

    // Prompt the user to enter a mathematical expression
    std::cout << "Aufgabe eingeben (z.B. 3 + 4 * 2 - 1): ";
    std::getline(std::cin, input); // Read the entire input line

    // Create a string stream from the input for parsing
    std::istringstream iss(input);

    // Parse and evaluate the expression
    const double result = parseTerm(iss);

    // Output the result of the evaluation
    std::cout << "Ergebnis: " << result << std::endl;

    return 0; // Indicate successful program termination
}
