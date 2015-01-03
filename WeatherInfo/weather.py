"""Author: Hannah Smith"""
from sys import argv
from urllib.request import urlopen
from json import loads


def get_weather(city):
	url = "http://api.openweathermap.org/data/2.5/forecast/daily?q=%s&mode=json&units=imperial&cnt=7" % city
	response = urlopen(url)
	content = response.read().decode()
	data = loads(content)
	i=0
	while i < 7:
		weather = data['list'][i]['weather'][0]['description']
		temp = data['list'][i]['temp']['day']
		print("Day",i+1, "weather for",city)
		i+=1
		print(weather)
		print("Temperature of",temp, "F°\n")
		
	
	
	


if __name__ == "__main__":
	if len(argv) < 1:
		print("Usage:  python3 weather.py city")
		exit(2)
		
	city = argv[1]
	get_weather(city)
	
	
