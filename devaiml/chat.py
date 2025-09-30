#
from groq import Groq
import json
import concurrent.futures

client = Groq(
    api_key="Nice_Try",
)

def get_response(i, prompt):
    chat_completion = client.chat.completions.create(
        messages=[
            {
                "role": "user",
                "content": prompt,
            }
        ],
        model="openai/gpt-oss-120b"
    )
    response = chat_completion.choices[0].message.content
    return (f"prompt_{i}", [prompt, response])

DATA = {}

# open file prompts.txt and read its content
with open("prompts.txt", "r") as file:
    prompts = file.readlines()

    # parallel requests for each prompt in prompts to save time
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(get_response, i, prompts[i]) for i in range(len(prompts))]
        for future in concurrent.futures.as_completed(futures):
            key, value = future.result()
            DATA[key] = value


with open("responses.json", "w") as file:
    json.dump(DATA, file, indent=4) 


        
