// from urllib.request import urlopen
// from urllib.parse import quote, urlparse, urlunparse, urljoin
// from json import loads
// import pyperclip


// var title = this.$('li.track.fav_track')[0].children[3].children[0].childNodes
// var artist = this.$('li.track.fav_track')[0].children[3].children[1].children[0].childNodes
// api = a43edad6a86e6e8948b072307593f34705eee82c

var title = "Brother (Kygo Remix)";
var artist = "Matt Corby";


function get_url(artist, title){
	var url = "https://gdata.youtube.com/feeds/api/videos?v=2&safeSearch=none&alt=json&max-results=1&q=%s+%s";
	var http = new XMLHttpRequest();
    http.open("GET", url + encodeURIComponent(title) + encodeURIComponent(artist), true);

http.onreadystatechange = function () {
        if (http.readyState == 4 && http.status == 200) {
            var response = http.responseText;
            var response = eval("(" + response + ")");
             print(response);

// var found = 0;
//             for (var i = 0; i < response.tracks.length && found == 0; i++) {
//                 if (trim(response.tracks[i].artists[0].name.toLowerCase()) == artist.toLowerCase()) {
//                     found = 1;
//                     i--; //because after for loop, there's the i++ so it won't give us the position of the song anymore!
                }
               

            }

// 	var content = response.read().decode()
// 	var data = loads(content)
// 	var link = data['feed']['entry'][0]['link'][0]['href']
// 	return link.strip('&feature=youtube_gdata')
// }

// var yturl = get_url(artist, title)
// pyperclip.copy(yturl)
// p = pyperclip.paste()

{
	"manifest_version": 2,
	"name":"MyTracks",
	"version": "versionString",

	"default_locale":"en",

	"page_action": {
		...
	}

	"content_scripts": [
	{
		"matches": ["*://8tracks.com/*/*"]
	}]
}

var myExtension = {
	myListener: function(evt) {
		alert("Received from web page: ") +
		evt.target.getAttribute("attribute1")
	}
}