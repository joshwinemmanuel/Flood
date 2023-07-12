



from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
import pyperclip
import time
import sys
from config import CHROME_PROFILE_PATH


options = webdriver.ChromeOptions()
options.add_argument(CHROME_PROFILE_PATH)

browser = webdriver.Chrome(
    executable_path='C:\chromedriver/chromedriver', options=options)

browser.maximize_window()

browser.get('https://web.whatsapp.com/')

with open('D:\Joshwin Emmanuel\Hannah\Python\src\groups.txt', 'r', encoding='utf8') as f:
    groups = [group.strip() for group in f.readlines()]

with open('D:\Joshwin Emmanuel\Hannah\Python\src\msg.txt', 'r', encoding='utf8') as f:
    msg = f.read()

for group in groups:
    search_xpath = '//div[@contenteditable="true"][@data-tab="3"]'

    search_box = WebDriverWait(browser, 500).until(
        EC.presence_of_element_located((By.XPATH, search_xpath))
    )

    search_box.clear()

    time.sleep(1)

    pyperclip.copy(group)

    search_box.send_keys(Keys.CONTROL + "v")  # Keys.CONTROL + "v"

    time.sleep(2)


    search_box.send_keys(Keys.ENTER)
  
    time.sleep(1)

    input_xpath = '//div[@contenteditable="true"][@data-tab="10"]' # 
    input_box = WebDriverWait(browser, 1000).until(
        EC.presence_of_element_located((By.XPATH, input_xpath))
    )


    pyperclip.copy(msg)
    input_box.send_keys(Keys.CONTROL + "v")  # Keys.CONTROL + "v"
    input_box.send_keys(Keys.ENTER)

    time.sleep(2)
    browser.close() #closes the browser
