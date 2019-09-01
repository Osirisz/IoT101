void setup() {
  Serial.begin(115200);
  // use String obj
//  String fName = "Earth";
//  String lName = "Osrisz";
//  String fullName = fName + lName;
  char fName[] = "Earth"; // it is a string
  char lName[] = "Osrisz";
  strcat(fName, lName); // value store to fName
  Serial.println(fName);
}

void loop() {
  // put your main code here, to run repeatedly:

}
