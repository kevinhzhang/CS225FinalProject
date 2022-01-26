# Data Processing Procedure
This is the script macro used to convert addresses, cities, and other locations into Latitude/Longitude data that can be qunatitatively represented over a geographical map, which uses Google's Geocoding API. We are including this script because we used it to prepare our dataset; it is used to convert the data to a valid format. This script is not our code, and we do not consider it to be a component of our final project. Instead, it is a resource we are using for the data collection process.

Source: https://pastebin.com/0NXMPwwg

Without this script, finding a dataset with valid parameters would be very difficult, or we would have to convert each location to quantative data manually. This file is included so our TA can understand our data collection process.

function GEOCODE_GOOGLE_LATITUDE(address) {
    if (address.map) {
        return address.map(GEOCODE_GOOGLE)
    } else {
        var r = Maps.newGeocoder().geocode(address)
        Utilities.sleep(1000)
        for (var i = 0; i < r.results.length; i++) {
            var res = r.results[i]
            return res.geometry.location.lat
        }
    }
}

function GEOCODE_GOOGLE_LONGITUDE(address) {
    if (address.map) {
        return address.map(GEOCODE_GOOGLE)
    } else {
        var r = Maps.newGeocoder().geocode(address)
        Utilities.sleep(1000)
        for (var i = 0; i < r.results.length; i++) {
            var res = r.results[i]
            return res.geometry.location.lng
        }
    }
}


This was a short script we wrote so that the geocoder script could process our data:

function addIL(name) {
    return adress + ", IL"
}

This was a short script we wrote to eliminate towns and locations that failed to be adequately located by the Geocoder:

function inRange( ranged, max, min) {
  if(ranged < max && ranged > min) {
    return ranged; 
  }
  else {
    return null; 
  }

Unforunately, this means that the data will not be 100% accurate to the state of IL. However, we believe that even so our data is significant enough to be a representative sample and yield relevant insight into the demographic trends of the state in terms of geographical location. For instance, for our population dataset we were able to include 88% of IL's total recorded population. (Refer to dataset_1).

Original datasets will be included in this proposal directory for review if necessary. Processed datasets will be included in the main directory to be used. 
