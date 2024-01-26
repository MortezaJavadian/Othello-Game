void ToJson(info GameInfo, char FileName[]);

void FromJson(FILE *file, info *GameInfo);

void ChangeJson(info GameInfo,info copy[2], char FileName[], int TargetGame);

void RemoveJson(char FileName[], int TargetGame);