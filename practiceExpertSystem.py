import nltk
from nltk.sentiment.vader import SentimentIntensityAnalyzer
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Initialize NLTK
nltk.download('vader_lexicon')

class Employee:
    def __init__(
        self,
        name,
        domain,
        gender,
        completed_tasks,
        avg_work_hours,
        salary,
        previous_rating,
        presentations,
        experience,
        leaves,
        comments
    ):
        self.name = name
        self.domain = domain
        self.gender = gender
        self.completed_tasks = completed_tasks
        self.avg_work_hours = avg_work_hours
        self.salary = salary
        self.previous_rating = previous_rating
        self.presentations = presentations
        self.experience = experience
        self.leaves = leaves
        self.comments = comments

def evaluate_employee(employee):
    # Initialize score
    score = 0
    explanation = []

    # Scoring based on number of tasks successfully completed
    if employee.completed_tasks > 100:
        score += 3
        explanation.append("High number of completed tasks (+3).")
    elif employee.completed_tasks > 50:
        score += 2
        explanation.append("Moderate number of completed tasks (+2).")
    else:
        score += 1
        explanation.append("Low number of completed tasks (+1).")

    # Scoring based on average working hours per week
    if employee.avg_work_hours > 40:
        score += 1  # Extra effort
        explanation.append("Working more than 40 hours per week (+1).")
    elif employee.avg_work_hours < 30:
        score -= 1  # Potential underperformance
        explanation.append("Working less than 30 hours per week (-1).")

    # Scoring based on salary
    if employee.salary > 70000:
        score += 2
        explanation.append("High salary, indicating greater responsibility (+2).")
    elif employee.salary > 50000:
        score += 1
        explanation.append("Moderate salary (+1).")
    else:
        score -= 1
        explanation.append("Low salary (-1).")

    # Scoring based on previous performance rating
    if employee.previous_rating >= 4:
        score += 2
        explanation.append("Previous high performance rating (+2).")
    elif employee.previous_rating >= 3:
        score += 1
        explanation.append("Previous moderate performance rating (+1).")
    else:
        score -= 1
        explanation.append("Previous low performance rating (-1).")

    # Scoring based on number of presentations given
    if employee.presentations >= 10:
        score += 2
        explanation.append("Given at least 10 presentations, indicating leadership (+2).")
    elif employee.presentations >= 5:
        score += 1
        explanation.append("Given 5 to 9 presentations (+1).")

    # Scoring based on experience in years
    if employee.experience > 10:
        score += 2
        explanation.append("More than 10 years of experience (+2).")
    elif employee.experience > 5:
        score += 1
        explanation.append("5 to 10 years of experience (+1).")
    else:
        score -= 1
        explanation.append("Less than 5 years of experience (-1).")

    # Scoring based on leaves taken in the last year
    if employee.leaves > 20:
        score -= 2
        explanation.append("More than 20 leaves in the last year (-2).")
    elif employee.leaves > 10:
        score -= 1
        explanation.append("10 to 20 leaves in the last year (-1).")

    # Determine the final performance evaluation
    if score >= 8:
        evaluation = "Excellent"
    elif score >= 5:
        evaluation = "Good"
    elif score >= 3:
        evaluation = "Satisfactory"
    else:
        evaluation = "Needs Improvement"

    # Generate a final verdict based on the evaluation
    if evaluation == "Excellent":
        verdict = (
            "The employee has demonstrated outstanding performance across several key "
            "metrics. This individual should be recognized for their efforts and considered "
            "for leadership roles or promotions."
        )
    elif evaluation == "Good":
        verdict = (
            "\nThe employee has shown solid performance with a few areas for improvement. Encouragement and development opportunities could help this individual reach even greater heights."
        )
    elif evaluation == "Satisfactory":
        verdict = (
            "\nThe employee has met the basic performance expectations, but there's room for growth. Consider providing additional training or guidance to help this individual improve."
        )
    else:
        verdict = (
            "\nThe employee's performance is below expectations. Address the areas of concern and consider closer supervision or performance improvement plans."
        )

    # Return both the evaluation, explanation, and final verdict
    return evaluation, explanation, verdict

# Function to perform sentiment analysis on employee comments
def analyze_sentiment(comments):
    sid = SentimentIntensityAnalyzer()
    scores = []
    for comment in comments:
        score = sid.polarity_scores(comment)
        scores.append(score['compound'])
    return sum(scores) / len(scores)

# Function to predict employee performance using machine learning
def predict_performance(X, y):
    # Check if there's only one sample
    if len(X) == 1:
        print("Only one sample provided. Skipping train-test split.")
        clf = RandomForestClassifier(random_state=42)
        clf.fit(X, y)
        y_pred = clf.predict(X)
        accuracy = accuracy_score(y, y_pred)
    else:
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
        clf = RandomForestClassifier(random_state=42)
        clf.fit(X_train, y_train)
        y_pred = clf.predict(X_test)
        accuracy = accuracy_score(y_test, y_pred)
    return clf, accuracy


# Function to gather employee details and comments from user input
def get_employee_details_with_comments():
    print("\nEnter the following employee details:")
    name = input("\nName: ")
    domain = input("Domain of expertise: ")
    gender = input("Gender: ")
    completed_tasks = int(input("Number of tasks successfully completed: "))
    avg_work_hours = int(input("Average working hours per week: "))
    salary = int(input("Salary: "))
    previous_rating = float(input("Previous rating by the expert system (out of 5): "))
    presentations = int(input("Number of presentations given: "))
    experience = int(input("Experience (in years): "))
    leaves = int(input("Number of leaves in the last year: "))

    comments = []
    num_comments = int(input("Enter the number of comments or feedback: "))
    for i in range(num_comments):
        comment = input(f"Enter comment {i+1}: ")
        comments.append(comment)

    return Employee(
        name=name,
        domain=domain,
        gender=gender,
        completed_tasks=completed_tasks,
        avg_work_hours=avg_work_hours,
        salary=salary,
        previous_rating=previous_rating,
        presentations=presentations,
        experience=experience,
        leaves=leaves,
        comments=comments
    )

# Gather employee details and comments from the user
employee = get_employee_details_with_comments()

# Perform sentiment analysis on employee comments
sentiment_score = analyze_sentiment(employee.comments)

# Prepare data for machine learning
X = [[employee.completed_tasks, employee.avg_work_hours, employee.salary, 
      employee.previous_rating, employee.presentations, employee.experience, sentiment_score]]
y = [1]  # Assuming a binary classification where 1 indicates good performance

# Predict employee performance using machine learning
clf, accuracy = predict_performance(X, y)

# Evaluate the employee's performance and get the final verdict
performance_rating, explanation, verdict = evaluate_employee(employee)

# Display the final rating, detailed explanation, final verdict, and prediction accuracy
print(f"\nEmployee {employee.name} performance rating: {performance_rating}\n")
print("Explanation:")
for line in explanation:
    print(f"  - {line}")

print("\nFinal Verdict:")
print(verdict)

print("\nPrediction Accuracy:", accuracy)
