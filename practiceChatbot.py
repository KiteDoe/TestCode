import os
import json
from difflib import get_close_matches

current_directory = os.getcwd()

def load_knowledge_base(file_path):
    with open(file_path, 'r') as file:
        data = json.load(file)
    return data

def find_best_match(user_input, options):
    matches = get_close_matches(user_input, options, n=1, cutoff=0.4)
    return matches[0] if matches else None

def get_answer_for_question(question, knowledge_base, product_name):
    for q in knowledge_base["products"][product_name]["questions"]:
        if q["question"] == question:
            return q["answer"]
        
def save_knowledge_base(file_path, data):
    with open(file_path, 'w') as file:
        json.dump(data, file, indent=2)

def chatbot():
    knowledge_base = load_knowledge_base(f"{current_directory}/Final_Practice/knowledge_base.json")
    product_name = None

    while True:
        if not product_name:
            while True:
                product_input = input("Bot: Please specify product name:")
                best_product_match = find_best_match(product_input, knowledge_base["products"])

                if best_product_match and best_product_match != product_input:
                    confirmation = input(f"Do you mean {best_product_match} (yes or no):").lower()
                    if confirmation == "yes":
                        product_name = best_product_match
                        break
                    elif confirmation == "no":
                        print("Bot: Please specify a product from following list options")
                        print("Products: ", ', '.join(knowledge_base["products"].keys()))
                        continue
                    else:
                        print("Bot: Invalid input please respond with yes or no")
                elif best_product_match == product_input:
                    product_name = best_product_match
                    break
                else:
                    print("Sorry I don't have information about that product")
                    print("please select from: ", ', '.join(knowledge_base["products"].keys()))
            
            print("FoodBot: You've selected:", product_name)

        user_input = input("Customer: ").lower()
        if user_input == "exit":
            break

        if user_input == "change product":
            continue

        if product_name:
            best_question_match = find_best_match(user_input, [q["question"] for q in knowledge_base["products"][product_name]["questions"]])

            if best_question_match:
                answer = get_answer_for_question(best_question_match, knowledge_base, product_name)
                print(f"Bot: {answer}")
            else:
                print("Sorry I don't know the answer, teach me or 'skip'")
                new_answer = input("Customer: ").lower()

                if new_answer == "skip":
                    continue
                else:
                    knowledge_base["products"][product_name]["questions"].append({"question":user_input, "answer": new_answer})
                    save_knowledge_base(f"{current_directory}/Final_Practice/knowledge_base.json", knowledge_base)
                    print("Thank you")
        else:
            print("Bot: Specify the product you are asking about")
            print("Availabel Products: ", ', '.join(knowledge_base["products"].keys()))

if __name__ == "__main__":
    chatbot()