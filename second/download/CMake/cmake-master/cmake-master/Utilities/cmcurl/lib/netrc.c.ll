; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/netrc.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.passwd = type { i8*, i8*, i32, i32, i8*, i8*, i8* }

@.str = private unnamed_addr constant [5 x i8] c"HOME\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"%s%s%s\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.3 = private unnamed_addr constant [7 x i8] c".netrc\00", align 1
@Curl_cfree = external global void (i8*)*, align 8
@.str.4 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c" \09\0A\00", align 1
@.str.6 = private unnamed_addr constant [8 x i8] c"machine\00", align 1
@.str.7 = private unnamed_addr constant [8 x i8] c"default\00", align 1
@Curl_cstrdup = external global i8* (i8*)*, align 8
@.str.8 = private unnamed_addr constant [6 x i8] c"login\00", align 1
@.str.9 = private unnamed_addr constant [9 x i8] c"password\00", align 1

; Function Attrs: nounwind uwtable
define i32 @Curl_parsenetrc(i8* %host, i8** %loginp, i8** %passwordp, i8* %netrcfile) #0 !dbg !11 {
entry:
  %retval = alloca i32, align 4
  %host.addr = alloca i8*, align 8
  %loginp.addr = alloca i8**, align 8
  %passwordp.addr = alloca i8**, align 8
  %netrcfile.addr = alloca i8*, align 8
  %file = alloca %struct._IO_FILE*, align 8
  %retcode = alloca i32, align 4
  %specific_login = alloca i32, align 4
  %netrc_alloc = alloca i8, align 1
  %state = alloca i32, align 4
  %state_login = alloca i8, align 1
  %state_password = alloca i8, align 1
  %state_our_login = alloca i32, align 4
  %home_alloc = alloca i8, align 1
  %home = alloca i8*, align 8
  %pw = alloca %struct.passwd*, align 8
  %tok = alloca i8*, align 8
  %tok_buf = alloca i8*, align 8
  %done = alloca i8, align 1
  %netrcbuffer = alloca [256 x i8], align 16
  %netrcbuffsize = alloca i32, align 4
  store i8* %host, i8** %host.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %host.addr, metadata !23, metadata !24), !dbg !25
  store i8** %loginp, i8*** %loginp.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %loginp.addr, metadata !26, metadata !24), !dbg !27
  store i8** %passwordp, i8*** %passwordp.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %passwordp.addr, metadata !28, metadata !24), !dbg !29
  store i8* %netrcfile, i8** %netrcfile.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %netrcfile.addr, metadata !30, metadata !24), !dbg !31
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %file, metadata !32, metadata !24), !dbg !93
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !94, metadata !24), !dbg !95
  store i32 1, i32* %retcode, align 4, !dbg !95
  call void @llvm.dbg.declare(metadata i32* %specific_login, metadata !96, metadata !24), !dbg !97
  %0 = load i8**, i8*** %loginp.addr, align 8, !dbg !98
  %1 = load i8*, i8** %0, align 8, !dbg !99
  %tobool = icmp ne i8* %1, null, !dbg !99
  br i1 %tobool, label %land.rhs, label %land.end, !dbg !100

land.rhs:                                         ; preds = %entry
  %2 = load i8**, i8*** %loginp.addr, align 8, !dbg !101
  %3 = load i8*, i8** %2, align 8, !dbg !103
  %4 = load i8, i8* %3, align 1, !dbg !104
  %conv = sext i8 %4 to i32, !dbg !104
  %cmp = icmp ne i32 %conv, 0, !dbg !105
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %5 = phi i1 [ false, %entry ], [ %cmp, %land.rhs ]
  %land.ext = zext i1 %5 to i32, !dbg !106
  store i32 %land.ext, i32* %specific_login, align 4, !dbg !108
  call void @llvm.dbg.declare(metadata i8* %netrc_alloc, metadata !109, metadata !24), !dbg !111
  store i8 0, i8* %netrc_alloc, align 1, !dbg !111
  call void @llvm.dbg.declare(metadata i32* %state, metadata !112, metadata !24), !dbg !113
  store i32 0, i32* %state, align 4, !dbg !113
  call void @llvm.dbg.declare(metadata i8* %state_login, metadata !114, metadata !24), !dbg !115
  store i8 0, i8* %state_login, align 1, !dbg !115
  call void @llvm.dbg.declare(metadata i8* %state_password, metadata !116, metadata !24), !dbg !117
  store i8 0, i8* %state_password, align 1, !dbg !117
  call void @llvm.dbg.declare(metadata i32* %state_our_login, metadata !118, metadata !24), !dbg !119
  store i32 0, i32* %state_our_login, align 4, !dbg !119
  %6 = load i8*, i8** %netrcfile.addr, align 8, !dbg !120
  %tobool2 = icmp ne i8* %6, null, !dbg !120
  br i1 %tobool2, label %if.end20, label %if.then, !dbg !122

if.then:                                          ; preds = %land.end
  call void @llvm.dbg.declare(metadata i8* %home_alloc, metadata !123, metadata !24), !dbg !125
  store i8 0, i8* %home_alloc, align 1, !dbg !125
  call void @llvm.dbg.declare(metadata i8** %home, metadata !126, metadata !24), !dbg !127
  %call = call i8* @curl_getenv(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0)), !dbg !128
  store i8* %call, i8** %home, align 8, !dbg !127
  %7 = load i8*, i8** %home, align 8, !dbg !129
  %tobool3 = icmp ne i8* %7, null, !dbg !129
  br i1 %tobool3, label %if.then4, label %if.else, !dbg !131

if.then4:                                         ; preds = %if.then
  store i8 1, i8* %home_alloc, align 1, !dbg !132
  br label %if.end9, !dbg !134

if.else:                                          ; preds = %if.then
  call void @llvm.dbg.declare(metadata %struct.passwd** %pw, metadata !135, metadata !24), !dbg !151
  %call5 = call i32 @geteuid() #4, !dbg !152
  %call6 = call %struct.passwd* @getpwuid(i32 %call5), !dbg !153
  store %struct.passwd* %call6, %struct.passwd** %pw, align 8, !dbg !155
  %8 = load %struct.passwd*, %struct.passwd** %pw, align 8, !dbg !156
  %tobool7 = icmp ne %struct.passwd* %8, null, !dbg !156
  br i1 %tobool7, label %if.then8, label %if.end, !dbg !158

if.then8:                                         ; preds = %if.else
  %9 = load %struct.passwd*, %struct.passwd** %pw, align 8, !dbg !159
  %pw_dir = getelementptr inbounds %struct.passwd, %struct.passwd* %9, i32 0, i32 5, !dbg !161
  %10 = load i8*, i8** %pw_dir, align 8, !dbg !161
  store i8* %10, i8** %home, align 8, !dbg !162
  br label %if.end, !dbg !163

if.end:                                           ; preds = %if.then8, %if.else
  br label %if.end9

if.end9:                                          ; preds = %if.end, %if.then4
  %11 = load i8*, i8** %home, align 8, !dbg !164
  %tobool10 = icmp ne i8* %11, null, !dbg !164
  br i1 %tobool10, label %if.end12, label %if.then11, !dbg !166

if.then11:                                        ; preds = %if.end9
  %12 = load i32, i32* %retcode, align 4, !dbg !167
  store i32 %12, i32* %retval, align 4, !dbg !168
  br label %return, !dbg !168

if.end12:                                         ; preds = %if.end9
  %13 = load i8*, i8** %home, align 8, !dbg !169
  %call13 = call i8* (i8*, ...) @curl_maprintf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i8* %13, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0)), !dbg !170
  store i8* %call13, i8** %netrcfile.addr, align 8, !dbg !171
  %14 = load i8, i8* %home_alloc, align 1, !dbg !172
  %tobool14 = trunc i8 %14 to i1, !dbg !172
  br i1 %tobool14, label %if.then15, label %if.end16, !dbg !174

if.then15:                                        ; preds = %if.end12
  %15 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !175
  %16 = load i8*, i8** %home, align 8, !dbg !175
  call void %15(i8* %16), !dbg !175
  br label %if.end16, !dbg !175

if.end16:                                         ; preds = %if.then15, %if.end12
  %17 = load i8*, i8** %netrcfile.addr, align 8, !dbg !176
  %tobool17 = icmp ne i8* %17, null, !dbg !176
  br i1 %tobool17, label %if.end19, label %if.then18, !dbg !178

if.then18:                                        ; preds = %if.end16
  store i32 -1, i32* %retval, align 4, !dbg !179
  br label %return, !dbg !179

if.end19:                                         ; preds = %if.end16
  store i8 1, i8* %netrc_alloc, align 1, !dbg !181
  br label %if.end20, !dbg !182

if.end20:                                         ; preds = %if.end19, %land.end
  %18 = load i8*, i8** %netrcfile.addr, align 8, !dbg !183
  %call21 = call %struct._IO_FILE* @fopen64(i8* %18, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i32 0, i32 0)), !dbg !184
  store %struct._IO_FILE* %call21, %struct._IO_FILE** %file, align 8, !dbg !185
  %19 = load i8, i8* %netrc_alloc, align 1, !dbg !186
  %tobool22 = trunc i8 %19 to i1, !dbg !186
  br i1 %tobool22, label %if.then23, label %if.end24, !dbg !188

if.then23:                                        ; preds = %if.end20
  %20 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !189
  %21 = load i8*, i8** %netrcfile.addr, align 8, !dbg !189
  call void %20(i8* %21), !dbg !189
  br label %if.end24, !dbg !189

if.end24:                                         ; preds = %if.then23, %if.end20
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** %file, align 8, !dbg !190
  %tobool25 = icmp ne %struct._IO_FILE* %22, null, !dbg !190
  br i1 %tobool25, label %if.then26, label %if.end110, !dbg !192

if.then26:                                        ; preds = %if.end24
  call void @llvm.dbg.declare(metadata i8** %tok, metadata !193, metadata !24), !dbg !195
  call void @llvm.dbg.declare(metadata i8** %tok_buf, metadata !196, metadata !24), !dbg !197
  call void @llvm.dbg.declare(metadata i8* %done, metadata !198, metadata !24), !dbg !199
  store i8 0, i8* %done, align 1, !dbg !199
  call void @llvm.dbg.declare(metadata [256 x i8]* %netrcbuffer, metadata !200, metadata !24), !dbg !204
  call void @llvm.dbg.declare(metadata i32* %netrcbuffsize, metadata !205, metadata !24), !dbg !206
  store i32 256, i32* %netrcbuffsize, align 4, !dbg !206
  br label %while.cond, !dbg !207

while.cond:                                       ; preds = %while.end, %if.then26
  %23 = load i8, i8* %done, align 1, !dbg !208
  %tobool27 = trunc i8 %23 to i1, !dbg !208
  br i1 %tobool27, label %land.end31, label %land.rhs28, !dbg !210

land.rhs28:                                       ; preds = %while.cond
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %netrcbuffer, i32 0, i32 0, !dbg !211
  %24 = load i32, i32* %netrcbuffsize, align 4, !dbg !213
  %25 = load %struct._IO_FILE*, %struct._IO_FILE** %file, align 8, !dbg !214
  %call29 = call i8* @fgets(i8* %arraydecay, i32 %24, %struct._IO_FILE* %25), !dbg !215
  %tobool30 = icmp ne i8* %call29, null, !dbg !216
  br label %land.end31

land.end31:                                       ; preds = %land.rhs28, %while.cond
  %26 = phi i1 [ false, %while.cond ], [ %tobool30, %land.rhs28 ]
  br i1 %26, label %while.body, label %while.end108, !dbg !217

while.body:                                       ; preds = %land.end31
  %arraydecay33 = getelementptr inbounds [256 x i8], [256 x i8]* %netrcbuffer, i32 0, i32 0, !dbg !219
  %call34 = call i8* @strtok_r(i8* %arraydecay33, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i8** %tok_buf) #4, !dbg !221
  store i8* %call34, i8** %tok, align 8, !dbg !222
  br label %while.cond35, !dbg !223

while.cond35:                                     ; preds = %sw.epilog, %while.body
  %27 = load i8, i8* %done, align 1, !dbg !224
  %tobool36 = trunc i8 %27 to i1, !dbg !224
  br i1 %tobool36, label %land.end39, label %land.rhs37, !dbg !226

land.rhs37:                                       ; preds = %while.cond35
  %28 = load i8*, i8** %tok, align 8, !dbg !227
  %tobool38 = icmp ne i8* %28, null, !dbg !229
  br label %land.end39

land.end39:                                       ; preds = %land.rhs37, %while.cond35
  %29 = phi i1 [ false, %while.cond35 ], [ %tobool38, %land.rhs37 ]
  br i1 %29, label %while.body41, label %while.end, !dbg !230

while.body41:                                     ; preds = %land.end39
  %30 = load i8**, i8*** %loginp.addr, align 8, !dbg !232
  %31 = load i8*, i8** %30, align 8, !dbg !235
  %tobool42 = icmp ne i8* %31, null, !dbg !235
  br i1 %tobool42, label %land.lhs.true, label %if.end51, !dbg !236

land.lhs.true:                                    ; preds = %while.body41
  %32 = load i8**, i8*** %loginp.addr, align 8, !dbg !237
  %33 = load i8*, i8** %32, align 8, !dbg !239
  %34 = load i8, i8* %33, align 1, !dbg !240
  %conv43 = sext i8 %34 to i32, !dbg !240
  %tobool44 = icmp ne i32 %conv43, 0, !dbg !240
  br i1 %tobool44, label %land.lhs.true45, label %if.end51, !dbg !241

land.lhs.true45:                                  ; preds = %land.lhs.true
  %35 = load i8**, i8*** %passwordp.addr, align 8, !dbg !242
  %36 = load i8*, i8** %35, align 8, !dbg !244
  %tobool46 = icmp ne i8* %36, null, !dbg !244
  br i1 %tobool46, label %land.lhs.true47, label %if.end51, !dbg !245

land.lhs.true47:                                  ; preds = %land.lhs.true45
  %37 = load i8**, i8*** %passwordp.addr, align 8, !dbg !246
  %38 = load i8*, i8** %37, align 8, !dbg !248
  %39 = load i8, i8* %38, align 1, !dbg !249
  %conv48 = sext i8 %39 to i32, !dbg !249
  %tobool49 = icmp ne i32 %conv48, 0, !dbg !249
  br i1 %tobool49, label %if.then50, label %if.end51, !dbg !250

if.then50:                                        ; preds = %land.lhs.true47
  store i8 1, i8* %done, align 1, !dbg !251
  br label %while.end, !dbg !253

if.end51:                                         ; preds = %land.lhs.true47, %land.lhs.true45, %land.lhs.true, %while.body41
  %40 = load i32, i32* %state, align 4, !dbg !254
  switch i32 %40, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb61
    i32 2, label %sw.bb67
  ], !dbg !255

sw.bb:                                            ; preds = %if.end51
  %41 = load i8*, i8** %tok, align 8, !dbg !256
  %call52 = call i32 @Curl_strcasecompare(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.6, i32 0, i32 0), i8* %41), !dbg !256
  %tobool53 = icmp ne i32 %call52, 0, !dbg !256
  br i1 %tobool53, label %if.then54, label %if.else55, !dbg !259

if.then54:                                        ; preds = %sw.bb
  store i32 1, i32* %state, align 4, !dbg !260
  br label %if.end60, !dbg !262

if.else55:                                        ; preds = %sw.bb
  %42 = load i8*, i8** %tok, align 8, !dbg !263
  %call56 = call i32 @Curl_strcasecompare(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.7, i32 0, i32 0), i8* %42), !dbg !263
  %tobool57 = icmp ne i32 %call56, 0, !dbg !263
  br i1 %tobool57, label %if.then58, label %if.end59, !dbg !265

if.then58:                                        ; preds = %if.else55
  store i32 2, i32* %state, align 4, !dbg !266
  store i32 0, i32* %retcode, align 4, !dbg !268
  br label %if.end59, !dbg !269

if.end59:                                         ; preds = %if.then58, %if.else55
  br label %if.end60

if.end60:                                         ; preds = %if.end59, %if.then54
  br label %sw.epilog, !dbg !270

sw.bb61:                                          ; preds = %if.end51
  %43 = load i8*, i8** %host.addr, align 8, !dbg !271
  %44 = load i8*, i8** %tok, align 8, !dbg !271
  %call62 = call i32 @Curl_strcasecompare(i8* %43, i8* %44), !dbg !271
  %tobool63 = icmp ne i32 %call62, 0, !dbg !271
  br i1 %tobool63, label %if.then64, label %if.else65, !dbg !273

if.then64:                                        ; preds = %sw.bb61
  store i32 2, i32* %state, align 4, !dbg !274
  store i32 0, i32* %retcode, align 4, !dbg !276
  br label %if.end66, !dbg !277

if.else65:                                        ; preds = %sw.bb61
  store i32 0, i32* %state, align 4, !dbg !278
  br label %if.end66

if.end66:                                         ; preds = %if.else65, %if.then64
  br label %sw.epilog, !dbg !279

sw.bb67:                                          ; preds = %if.end51
  %45 = load i8, i8* %state_login, align 1, !dbg !280
  %tobool68 = icmp ne i8 %45, 0, !dbg !280
  br i1 %tobool68, label %if.then69, label %if.else79, !dbg !282

if.then69:                                        ; preds = %sw.bb67
  %46 = load i32, i32* %specific_login, align 4, !dbg !283
  %tobool70 = icmp ne i32 %46, 0, !dbg !283
  br i1 %tobool70, label %if.then71, label %if.else73, !dbg !286

if.then71:                                        ; preds = %if.then69
  %47 = load i8**, i8*** %loginp.addr, align 8, !dbg !287
  %48 = load i8*, i8** %47, align 8, !dbg !287
  %49 = load i8*, i8** %tok, align 8, !dbg !287
  %call72 = call i32 @Curl_strcasecompare(i8* %48, i8* %49), !dbg !287
  store i32 %call72, i32* %state_our_login, align 4, !dbg !289
  br label %if.end78, !dbg !290

if.else73:                                        ; preds = %if.then69
  %50 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !291
  %51 = load i8**, i8*** %loginp.addr, align 8, !dbg !291
  %52 = load i8*, i8** %51, align 8, !dbg !291
  call void %50(i8* %52), !dbg !291
  %53 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !293
  %54 = load i8*, i8** %tok, align 8, !dbg !293
  %call74 = call i8* %53(i8* %54), !dbg !293
  %55 = load i8**, i8*** %loginp.addr, align 8, !dbg !294
  store i8* %call74, i8** %55, align 8, !dbg !295
  %56 = load i8**, i8*** %loginp.addr, align 8, !dbg !296
  %57 = load i8*, i8** %56, align 8, !dbg !298
  %tobool75 = icmp ne i8* %57, null, !dbg !298
  br i1 %tobool75, label %if.end77, label %if.then76, !dbg !299

if.then76:                                        ; preds = %if.else73
  store i32 -1, i32* %retcode, align 4, !dbg !300
  br label %out, !dbg !302

if.end77:                                         ; preds = %if.else73
  br label %if.end78

if.end78:                                         ; preds = %if.end77, %if.then71
  store i8 0, i8* %state_login, align 1, !dbg !303
  br label %if.end106, !dbg !304

if.else79:                                        ; preds = %sw.bb67
  %58 = load i8, i8* %state_password, align 1, !dbg !305
  %tobool80 = icmp ne i8 %58, 0, !dbg !305
  br i1 %tobool80, label %if.then81, label %if.else90, !dbg !307

if.then81:                                        ; preds = %if.else79
  %59 = load i32, i32* %state_our_login, align 4, !dbg !308
  %tobool82 = icmp ne i32 %59, 0, !dbg !308
  br i1 %tobool82, label %if.then84, label %lor.lhs.false, !dbg !311

lor.lhs.false:                                    ; preds = %if.then81
  %60 = load i32, i32* %specific_login, align 4, !dbg !312
  %tobool83 = icmp ne i32 %60, 0, !dbg !312
  br i1 %tobool83, label %if.end89, label %if.then84, !dbg !314

if.then84:                                        ; preds = %lor.lhs.false, %if.then81
  %61 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !315
  %62 = load i8**, i8*** %passwordp.addr, align 8, !dbg !315
  %63 = load i8*, i8** %62, align 8, !dbg !315
  call void %61(i8* %63), !dbg !315
  %64 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !317
  %65 = load i8*, i8** %tok, align 8, !dbg !317
  %call85 = call i8* %64(i8* %65), !dbg !317
  %66 = load i8**, i8*** %passwordp.addr, align 8, !dbg !318
  store i8* %call85, i8** %66, align 8, !dbg !319
  %67 = load i8**, i8*** %passwordp.addr, align 8, !dbg !320
  %68 = load i8*, i8** %67, align 8, !dbg !322
  %tobool86 = icmp ne i8* %68, null, !dbg !322
  br i1 %tobool86, label %if.end88, label %if.then87, !dbg !323

if.then87:                                        ; preds = %if.then84
  store i32 -1, i32* %retcode, align 4, !dbg !324
  br label %out, !dbg !326

if.end88:                                         ; preds = %if.then84
  br label %if.end89, !dbg !327

if.end89:                                         ; preds = %if.end88, %lor.lhs.false
  store i8 0, i8* %state_password, align 1, !dbg !328
  br label %if.end105, !dbg !329

if.else90:                                        ; preds = %if.else79
  %69 = load i8*, i8** %tok, align 8, !dbg !330
  %call91 = call i32 @Curl_strcasecompare(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.8, i32 0, i32 0), i8* %69), !dbg !330
  %tobool92 = icmp ne i32 %call91, 0, !dbg !330
  br i1 %tobool92, label %if.then93, label %if.else94, !dbg !332

if.then93:                                        ; preds = %if.else90
  store i8 1, i8* %state_login, align 1, !dbg !333
  br label %if.end104, !dbg !334

if.else94:                                        ; preds = %if.else90
  %70 = load i8*, i8** %tok, align 8, !dbg !335
  %call95 = call i32 @Curl_strcasecompare(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.9, i32 0, i32 0), i8* %70), !dbg !335
  %tobool96 = icmp ne i32 %call95, 0, !dbg !335
  br i1 %tobool96, label %if.then97, label %if.else98, !dbg !337

if.then97:                                        ; preds = %if.else94
  store i8 1, i8* %state_password, align 1, !dbg !338
  br label %if.end103, !dbg !339

if.else98:                                        ; preds = %if.else94
  %71 = load i8*, i8** %tok, align 8, !dbg !340
  %call99 = call i32 @Curl_strcasecompare(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.6, i32 0, i32 0), i8* %71), !dbg !340
  %tobool100 = icmp ne i32 %call99, 0, !dbg !340
  br i1 %tobool100, label %if.then101, label %if.end102, !dbg !342

if.then101:                                       ; preds = %if.else98
  store i32 1, i32* %state, align 4, !dbg !343
  store i32 0, i32* %state_our_login, align 4, !dbg !345
  br label %if.end102, !dbg !346

if.end102:                                        ; preds = %if.then101, %if.else98
  br label %if.end103

if.end103:                                        ; preds = %if.end102, %if.then97
  br label %if.end104

if.end104:                                        ; preds = %if.end103, %if.then93
  br label %if.end105

if.end105:                                        ; preds = %if.end104, %if.end89
  br label %if.end106

if.end106:                                        ; preds = %if.end105, %if.end78
  br label %sw.epilog, !dbg !347

sw.epilog:                                        ; preds = %if.end51, %if.end106, %if.end66, %if.end60
  %call107 = call i8* @strtok_r(i8* null, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i8** %tok_buf) #4, !dbg !348
  store i8* %call107, i8** %tok, align 8, !dbg !349
  br label %while.cond35, !dbg !350

while.end:                                        ; preds = %if.then50, %land.end39
  br label %while.cond, !dbg !352

while.end108:                                     ; preds = %land.end31
  br label %out, !dbg !354

out:                                              ; preds = %while.end108, %if.then87, %if.then76
  %72 = load %struct._IO_FILE*, %struct._IO_FILE** %file, align 8, !dbg !356
  %call109 = call i32 @fclose(%struct._IO_FILE* %72), !dbg !357
  br label %if.end110, !dbg !358

if.end110:                                        ; preds = %out, %if.end24
  %73 = load i32, i32* %retcode, align 4, !dbg !359
  store i32 %73, i32* %retval, align 4, !dbg !360
  br label %return, !dbg !360

return:                                           ; preds = %if.end110, %if.then18, %if.then11
  %74 = load i32, i32* %retval, align 4, !dbg !361
  ret i32 %74, !dbg !361
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i8* @curl_getenv(i8*) #2

declare %struct.passwd* @getpwuid(i32) #2

; Function Attrs: nounwind
declare i32 @geteuid() #3

declare i8* @curl_maprintf(i8*, ...) #2

declare %struct._IO_FILE* @fopen64(i8*, i8*) #2

declare i8* @fgets(i8*, i32, %struct._IO_FILE*) #2

; Function Attrs: nounwind
declare i8* @strtok_r(i8*, i8*, i8**) #3

declare i32 @Curl_strcasecompare(i8*, i8*) #2

declare i32 @fclose(%struct._IO_FILE*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!20, !21}
!llvm.ident = !{!22}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !8, subprograms: !10)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/netrc.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "host_lookup_state", file: !1, line: 41, size: 32, align: 32, elements: !4)
!4 = !{!5, !6, !7}
!5 = !DIEnumerator(name: "NOTHING", value: 0)
!6 = !DIEnumerator(name: "HOSTFOUND", value: 1)
!7 = !DIEnumerator(name: "HOSTVALID", value: 2)
!8 = !{!9}
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !{!11}
!11 = distinct !DISubprogram(name: "Curl_parsenetrc", scope: !1, file: !1, line: 53, type: !12, isLocal: false, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !19)
!12 = !DISubroutineType(types: !13)
!13 = !{!9, !14, !17, !17, !18}
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !16)
!16 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!19 = !{}
!20 = !{i32 2, !"Dwarf Version", i32 4}
!21 = !{i32 2, !"Debug Info Version", i32 3}
!22 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!23 = !DILocalVariable(name: "host", arg: 1, scope: !11, file: !1, line: 53, type: !14)
!24 = !DIExpression()
!25 = !DILocation(line: 53, column: 33, scope: !11)
!26 = !DILocalVariable(name: "loginp", arg: 2, scope: !11, file: !1, line: 54, type: !17)
!27 = !DILocation(line: 54, column: 28, scope: !11)
!28 = !DILocalVariable(name: "passwordp", arg: 3, scope: !11, file: !1, line: 55, type: !17)
!29 = !DILocation(line: 55, column: 28, scope: !11)
!30 = !DILocalVariable(name: "netrcfile", arg: 4, scope: !11, file: !1, line: 56, type: !18)
!31 = !DILocation(line: 56, column: 27, scope: !11)
!32 = !DILocalVariable(name: "file", scope: !11, file: !1, line: 58, type: !33)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !35, line: 48, baseType: !36)
!35 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !37, line: 245, size: 1728, align: 64, elements: !38)
!37 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!38 = !{!39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !59, !60, !61, !62, !66, !68, !70, !74, !77, !79, !81, !82, !83, !84, !88, !89}
!39 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !36, file: !37, line: 246, baseType: !9, size: 32, align: 32)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !36, file: !37, line: 251, baseType: !18, size: 64, align: 64, offset: 64)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !36, file: !37, line: 252, baseType: !18, size: 64, align: 64, offset: 128)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !36, file: !37, line: 253, baseType: !18, size: 64, align: 64, offset: 192)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !36, file: !37, line: 254, baseType: !18, size: 64, align: 64, offset: 256)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !36, file: !37, line: 255, baseType: !18, size: 64, align: 64, offset: 320)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !36, file: !37, line: 256, baseType: !18, size: 64, align: 64, offset: 384)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !36, file: !37, line: 257, baseType: !18, size: 64, align: 64, offset: 448)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !36, file: !37, line: 258, baseType: !18, size: 64, align: 64, offset: 512)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !36, file: !37, line: 260, baseType: !18, size: 64, align: 64, offset: 576)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !36, file: !37, line: 261, baseType: !18, size: 64, align: 64, offset: 640)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !36, file: !37, line: 262, baseType: !18, size: 64, align: 64, offset: 704)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !36, file: !37, line: 264, baseType: !52, size: 64, align: 64, offset: 768)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !37, line: 160, size: 192, align: 64, elements: !54)
!54 = !{!55, !56, !58}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !53, file: !37, line: 161, baseType: !52, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !53, file: !37, line: 162, baseType: !57, size: 64, align: 64, offset: 64)
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !53, file: !37, line: 166, baseType: !9, size: 32, align: 32, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !36, file: !37, line: 266, baseType: !57, size: 64, align: 64, offset: 832)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !36, file: !37, line: 268, baseType: !9, size: 32, align: 32, offset: 896)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !36, file: !37, line: 272, baseType: !9, size: 32, align: 32, offset: 928)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !36, file: !37, line: 274, baseType: !63, size: 64, align: 64, offset: 960)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !64, line: 131, baseType: !65)
!64 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!65 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !36, file: !37, line: 278, baseType: !67, size: 16, align: 16, offset: 1024)
!67 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !36, file: !37, line: 279, baseType: !69, size: 8, align: 8, offset: 1040)
!69 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !36, file: !37, line: 280, baseType: !71, size: 8, align: 8, offset: 1048)
!71 = !DICompositeType(tag: DW_TAG_array_type, baseType: !16, size: 8, align: 8, elements: !72)
!72 = !{!73}
!73 = !DISubrange(count: 1)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !36, file: !37, line: 284, baseType: !75, size: 64, align: 64, offset: 1088)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !37, line: 154, baseType: null)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !36, file: !37, line: 293, baseType: !78, size: 64, align: 64, offset: 1152)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !64, line: 132, baseType: !65)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !36, file: !37, line: 302, baseType: !80, size: 64, align: 64, offset: 1216)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !36, file: !37, line: 303, baseType: !80, size: 64, align: 64, offset: 1280)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !36, file: !37, line: 304, baseType: !80, size: 64, align: 64, offset: 1344)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !36, file: !37, line: 305, baseType: !80, size: 64, align: 64, offset: 1408)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !36, file: !37, line: 306, baseType: !85, size: 64, align: 64, offset: 1472)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !86, line: 62, baseType: !87)
!86 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!87 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !36, file: !37, line: 308, baseType: !9, size: 32, align: 32, offset: 1536)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !36, file: !37, line: 310, baseType: !90, size: 160, align: 8, offset: 1568)
!90 = !DICompositeType(tag: DW_TAG_array_type, baseType: !16, size: 160, align: 8, elements: !91)
!91 = !{!92}
!92 = !DISubrange(count: 20)
!93 = !DILocation(line: 58, column: 9, scope: !11)
!94 = !DILocalVariable(name: "retcode", scope: !11, file: !1, line: 59, type: !9)
!95 = !DILocation(line: 59, column: 7, scope: !11)
!96 = !DILocalVariable(name: "specific_login", scope: !11, file: !1, line: 60, type: !9)
!97 = !DILocation(line: 60, column: 7, scope: !11)
!98 = !DILocation(line: 60, column: 26, scope: !11)
!99 = !DILocation(line: 60, column: 25, scope: !11)
!100 = !DILocation(line: 60, column: 33, scope: !11)
!101 = !DILocation(line: 60, column: 38, scope: !102)
!102 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 1)
!103 = !DILocation(line: 60, column: 37, scope: !102)
!104 = !DILocation(line: 60, column: 36, scope: !102)
!105 = !DILocation(line: 60, column: 45, scope: !102)
!106 = !DILocation(line: 60, column: 33, scope: !107)
!107 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 2)
!108 = !DILocation(line: 60, column: 7, scope: !107)
!109 = !DILocalVariable(name: "netrc_alloc", scope: !11, file: !1, line: 61, type: !110)
!110 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!111 = !DILocation(line: 61, column: 8, scope: !11)
!112 = !DILocalVariable(name: "state", scope: !11, file: !1, line: 62, type: !3)
!113 = !DILocation(line: 62, column: 26, scope: !11)
!114 = !DILocalVariable(name: "state_login", scope: !11, file: !1, line: 64, type: !16)
!115 = !DILocation(line: 64, column: 8, scope: !11)
!116 = !DILocalVariable(name: "state_password", scope: !11, file: !1, line: 65, type: !16)
!117 = !DILocation(line: 65, column: 8, scope: !11)
!118 = !DILocalVariable(name: "state_our_login", scope: !11, file: !1, line: 66, type: !9)
!119 = !DILocation(line: 66, column: 7, scope: !11)
!120 = !DILocation(line: 70, column: 7, scope: !121)
!121 = distinct !DILexicalBlock(scope: !11, file: !1, line: 70, column: 6)
!122 = !DILocation(line: 70, column: 6, scope: !11)
!123 = !DILocalVariable(name: "home_alloc", scope: !124, file: !1, line: 71, type: !110)
!124 = distinct !DILexicalBlock(scope: !121, file: !1, line: 70, column: 18)
!125 = !DILocation(line: 71, column: 10, scope: !124)
!126 = !DILocalVariable(name: "home", scope: !124, file: !1, line: 72, type: !18)
!127 = !DILocation(line: 72, column: 11, scope: !124)
!128 = !DILocation(line: 72, column: 18, scope: !124)
!129 = !DILocation(line: 73, column: 8, scope: !130)
!130 = distinct !DILexicalBlock(scope: !124, file: !1, line: 73, column: 8)
!131 = !DILocation(line: 73, column: 8, scope: !124)
!132 = !DILocation(line: 74, column: 18, scope: !133)
!133 = distinct !DILexicalBlock(scope: !130, file: !1, line: 73, column: 14)
!134 = !DILocation(line: 88, column: 5, scope: !133)
!135 = !DILocalVariable(name: "pw", scope: !136, file: !1, line: 90, type: !137)
!136 = distinct !DILexicalBlock(scope: !130, file: !1, line: 89, column: 10)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "passwd", file: !139, line: 49, size: 384, align: 64, elements: !140)
!139 = !DIFile(filename: "/usr/include/pwd.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!140 = !{!141, !142, !143, !146, !148, !149, !150}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "pw_name", scope: !138, file: !139, line: 51, baseType: !18, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "pw_passwd", scope: !138, file: !139, line: 52, baseType: !18, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "pw_uid", scope: !138, file: !139, line: 53, baseType: !144, size: 32, align: 32, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !64, line: 125, baseType: !145)
!145 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gid", scope: !138, file: !139, line: 54, baseType: !147, size: 32, align: 32, offset: 160)
!147 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !64, line: 126, baseType: !145)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gecos", scope: !138, file: !139, line: 55, baseType: !18, size: 64, align: 64, offset: 192)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "pw_dir", scope: !138, file: !139, line: 56, baseType: !18, size: 64, align: 64, offset: 256)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "pw_shell", scope: !138, file: !139, line: 57, baseType: !18, size: 64, align: 64, offset: 320)
!151 = !DILocation(line: 90, column: 22, scope: !136)
!152 = !DILocation(line: 91, column: 20, scope: !136)
!153 = !DILocation(line: 91, column: 11, scope: !154)
!154 = !DILexicalBlockFile(scope: !136, file: !1, discriminator: 1)
!155 = !DILocation(line: 91, column: 9, scope: !136)
!156 = !DILocation(line: 92, column: 10, scope: !157)
!157 = distinct !DILexicalBlock(scope: !136, file: !1, line: 92, column: 10)
!158 = !DILocation(line: 92, column: 10, scope: !136)
!159 = !DILocation(line: 93, column: 16, scope: !160)
!160 = distinct !DILexicalBlock(scope: !157, file: !1, line: 92, column: 14)
!161 = !DILocation(line: 93, column: 20, scope: !160)
!162 = !DILocation(line: 93, column: 14, scope: !160)
!163 = !DILocation(line: 94, column: 7, scope: !160)
!164 = !DILocation(line: 98, column: 9, scope: !165)
!165 = distinct !DILexicalBlock(scope: !124, file: !1, line: 98, column: 8)
!166 = !DILocation(line: 98, column: 8, scope: !124)
!167 = !DILocation(line: 99, column: 14, scope: !165)
!168 = !DILocation(line: 99, column: 7, scope: !165)
!169 = !DILocation(line: 101, column: 41, scope: !124)
!170 = !DILocation(line: 101, column: 17, scope: !124)
!171 = !DILocation(line: 101, column: 15, scope: !124)
!172 = !DILocation(line: 102, column: 8, scope: !173)
!173 = distinct !DILexicalBlock(scope: !124, file: !1, line: 102, column: 8)
!174 = !DILocation(line: 102, column: 8, scope: !124)
!175 = !DILocation(line: 103, column: 7, scope: !173)
!176 = !DILocation(line: 104, column: 9, scope: !177)
!177 = distinct !DILexicalBlock(scope: !124, file: !1, line: 104, column: 8)
!178 = !DILocation(line: 104, column: 8, scope: !124)
!179 = !DILocation(line: 105, column: 7, scope: !180)
!180 = distinct !DILexicalBlock(scope: !177, file: !1, line: 104, column: 20)
!181 = !DILocation(line: 107, column: 17, scope: !124)
!182 = !DILocation(line: 108, column: 3, scope: !124)
!183 = !DILocation(line: 110, column: 16, scope: !11)
!184 = !DILocation(line: 110, column: 10, scope: !11)
!185 = !DILocation(line: 110, column: 8, scope: !11)
!186 = !DILocation(line: 111, column: 6, scope: !187)
!187 = distinct !DILexicalBlock(scope: !11, file: !1, line: 111, column: 6)
!188 = !DILocation(line: 111, column: 6, scope: !11)
!189 = !DILocation(line: 112, column: 5, scope: !187)
!190 = !DILocation(line: 113, column: 6, scope: !191)
!191 = distinct !DILexicalBlock(scope: !11, file: !1, line: 113, column: 6)
!192 = !DILocation(line: 113, column: 6, scope: !11)
!193 = !DILocalVariable(name: "tok", scope: !194, file: !1, line: 114, type: !18)
!194 = distinct !DILexicalBlock(scope: !191, file: !1, line: 113, column: 12)
!195 = !DILocation(line: 114, column: 11, scope: !194)
!196 = !DILocalVariable(name: "tok_buf", scope: !194, file: !1, line: 115, type: !18)
!197 = !DILocation(line: 115, column: 11, scope: !194)
!198 = !DILocalVariable(name: "done", scope: !194, file: !1, line: 116, type: !110)
!199 = !DILocation(line: 116, column: 10, scope: !194)
!200 = !DILocalVariable(name: "netrcbuffer", scope: !194, file: !1, line: 117, type: !201)
!201 = !DICompositeType(tag: DW_TAG_array_type, baseType: !16, size: 2048, align: 8, elements: !202)
!202 = !{!203}
!203 = !DISubrange(count: 256)
!204 = !DILocation(line: 117, column: 10, scope: !194)
!205 = !DILocalVariable(name: "netrcbuffsize", scope: !194, file: !1, line: 118, type: !9)
!206 = !DILocation(line: 118, column: 10, scope: !194)
!207 = !DILocation(line: 120, column: 5, scope: !194)
!208 = !DILocation(line: 120, column: 12, scope: !209)
!209 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 1)
!210 = !DILocation(line: 120, column: 17, scope: !209)
!211 = !DILocation(line: 120, column: 26, scope: !212)
!212 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 2)
!213 = !DILocation(line: 120, column: 39, scope: !212)
!214 = !DILocation(line: 120, column: 54, scope: !212)
!215 = !DILocation(line: 120, column: 20, scope: !212)
!216 = !DILocation(line: 120, column: 17, scope: !212)
!217 = !DILocation(line: 120, column: 5, scope: !218)
!218 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 3)
!219 = !DILocation(line: 121, column: 20, scope: !220)
!220 = distinct !DILexicalBlock(scope: !194, file: !1, line: 120, column: 61)
!221 = !DILocation(line: 121, column: 11, scope: !220)
!222 = !DILocation(line: 121, column: 10, scope: !220)
!223 = !DILocation(line: 122, column: 7, scope: !220)
!224 = !DILocation(line: 122, column: 14, scope: !225)
!225 = !DILexicalBlockFile(scope: !220, file: !1, discriminator: 1)
!226 = !DILocation(line: 122, column: 19, scope: !225)
!227 = !DILocation(line: 122, column: 22, scope: !228)
!228 = !DILexicalBlockFile(scope: !220, file: !1, discriminator: 2)
!229 = !DILocation(line: 122, column: 19, scope: !228)
!230 = !DILocation(line: 122, column: 7, scope: !231)
!231 = !DILexicalBlockFile(scope: !220, file: !1, discriminator: 3)
!232 = !DILocation(line: 124, column: 14, scope: !233)
!233 = distinct !DILexicalBlock(scope: !234, file: !1, line: 124, column: 12)
!234 = distinct !DILexicalBlock(scope: !220, file: !1, line: 122, column: 27)
!235 = !DILocation(line: 124, column: 13, scope: !233)
!236 = !DILocation(line: 124, column: 21, scope: !233)
!237 = !DILocation(line: 124, column: 26, scope: !238)
!238 = !DILexicalBlockFile(scope: !233, file: !1, discriminator: 1)
!239 = !DILocation(line: 124, column: 25, scope: !238)
!240 = !DILocation(line: 124, column: 24, scope: !238)
!241 = !DILocation(line: 124, column: 34, scope: !238)
!242 = !DILocation(line: 124, column: 39, scope: !243)
!243 = !DILexicalBlockFile(scope: !233, file: !1, discriminator: 2)
!244 = !DILocation(line: 124, column: 38, scope: !243)
!245 = !DILocation(line: 124, column: 49, scope: !243)
!246 = !DILocation(line: 124, column: 54, scope: !247)
!247 = !DILexicalBlockFile(scope: !233, file: !1, discriminator: 3)
!248 = !DILocation(line: 124, column: 53, scope: !247)
!249 = !DILocation(line: 124, column: 52, scope: !247)
!250 = !DILocation(line: 124, column: 12, scope: !247)
!251 = !DILocation(line: 125, column: 15, scope: !252)
!252 = distinct !DILexicalBlock(scope: !233, file: !1, line: 124, column: 66)
!253 = !DILocation(line: 126, column: 11, scope: !252)
!254 = !DILocation(line: 129, column: 16, scope: !234)
!255 = !DILocation(line: 129, column: 9, scope: !234)
!256 = !DILocation(line: 131, column: 14, scope: !257)
!257 = distinct !DILexicalBlock(scope: !258, file: !1, line: 131, column: 14)
!258 = distinct !DILexicalBlock(scope: !234, file: !1, line: 129, column: 23)
!259 = !DILocation(line: 131, column: 14, scope: !258)
!260 = !DILocation(line: 136, column: 18, scope: !261)
!261 = distinct !DILexicalBlock(scope: !257, file: !1, line: 131, column: 46)
!262 = !DILocation(line: 137, column: 11, scope: !261)
!263 = !DILocation(line: 138, column: 19, scope: !264)
!264 = distinct !DILexicalBlock(scope: !257, file: !1, line: 138, column: 19)
!265 = !DILocation(line: 138, column: 19, scope: !257)
!266 = !DILocation(line: 139, column: 18, scope: !267)
!267 = distinct !DILexicalBlock(scope: !264, file: !1, line: 138, column: 51)
!268 = !DILocation(line: 140, column: 20, scope: !267)
!269 = !DILocation(line: 141, column: 11, scope: !267)
!270 = !DILocation(line: 142, column: 11, scope: !258)
!271 = !DILocation(line: 144, column: 14, scope: !272)
!272 = distinct !DILexicalBlock(scope: !258, file: !1, line: 144, column: 14)
!273 = !DILocation(line: 144, column: 14, scope: !258)
!274 = !DILocation(line: 146, column: 18, scope: !275)
!275 = distinct !DILexicalBlock(scope: !272, file: !1, line: 144, column: 41)
!276 = !DILocation(line: 147, column: 20, scope: !275)
!277 = !DILocation(line: 148, column: 11, scope: !275)
!278 = !DILocation(line: 151, column: 18, scope: !272)
!279 = !DILocation(line: 152, column: 11, scope: !258)
!280 = !DILocation(line: 155, column: 14, scope: !281)
!281 = distinct !DILexicalBlock(scope: !258, file: !1, line: 155, column: 14)
!282 = !DILocation(line: 155, column: 14, scope: !258)
!283 = !DILocation(line: 156, column: 16, scope: !284)
!284 = distinct !DILexicalBlock(scope: !285, file: !1, line: 156, column: 16)
!285 = distinct !DILexicalBlock(scope: !281, file: !1, line: 155, column: 27)
!286 = !DILocation(line: 156, column: 16, scope: !285)
!287 = !DILocation(line: 157, column: 33, scope: !288)
!288 = distinct !DILexicalBlock(scope: !284, file: !1, line: 156, column: 32)
!289 = !DILocation(line: 157, column: 31, scope: !288)
!290 = !DILocation(line: 158, column: 13, scope: !288)
!291 = !DILocation(line: 160, column: 15, scope: !292)
!292 = distinct !DILexicalBlock(scope: !284, file: !1, line: 159, column: 18)
!293 = !DILocation(line: 161, column: 25, scope: !292)
!294 = !DILocation(line: 161, column: 16, scope: !292)
!295 = !DILocation(line: 161, column: 23, scope: !292)
!296 = !DILocation(line: 162, column: 20, scope: !297)
!297 = distinct !DILexicalBlock(scope: !292, file: !1, line: 162, column: 18)
!298 = !DILocation(line: 162, column: 19, scope: !297)
!299 = !DILocation(line: 162, column: 18, scope: !292)
!300 = !DILocation(line: 163, column: 25, scope: !301)
!301 = distinct !DILexicalBlock(scope: !297, file: !1, line: 162, column: 28)
!302 = !DILocation(line: 164, column: 17, scope: !301)
!303 = !DILocation(line: 167, column: 24, scope: !285)
!304 = !DILocation(line: 168, column: 11, scope: !285)
!305 = !DILocation(line: 169, column: 19, scope: !306)
!306 = distinct !DILexicalBlock(scope: !281, file: !1, line: 169, column: 19)
!307 = !DILocation(line: 169, column: 19, scope: !281)
!308 = !DILocation(line: 170, column: 16, scope: !309)
!309 = distinct !DILexicalBlock(scope: !310, file: !1, line: 170, column: 16)
!310 = distinct !DILexicalBlock(scope: !306, file: !1, line: 169, column: 35)
!311 = !DILocation(line: 170, column: 32, scope: !309)
!312 = !DILocation(line: 170, column: 36, scope: !313)
!313 = !DILexicalBlockFile(scope: !309, file: !1, discriminator: 1)
!314 = !DILocation(line: 170, column: 16, scope: !313)
!315 = !DILocation(line: 171, column: 15, scope: !316)
!316 = distinct !DILexicalBlock(scope: !309, file: !1, line: 170, column: 52)
!317 = !DILocation(line: 172, column: 28, scope: !316)
!318 = !DILocation(line: 172, column: 16, scope: !316)
!319 = !DILocation(line: 172, column: 26, scope: !316)
!320 = !DILocation(line: 173, column: 20, scope: !321)
!321 = distinct !DILexicalBlock(scope: !316, file: !1, line: 173, column: 18)
!322 = !DILocation(line: 173, column: 19, scope: !321)
!323 = !DILocation(line: 173, column: 18, scope: !316)
!324 = !DILocation(line: 174, column: 25, scope: !325)
!325 = distinct !DILexicalBlock(scope: !321, file: !1, line: 173, column: 31)
!326 = !DILocation(line: 175, column: 17, scope: !325)
!327 = !DILocation(line: 177, column: 13, scope: !316)
!328 = !DILocation(line: 178, column: 27, scope: !310)
!329 = !DILocation(line: 179, column: 11, scope: !310)
!330 = !DILocation(line: 180, column: 19, scope: !331)
!331 = distinct !DILexicalBlock(scope: !306, file: !1, line: 180, column: 19)
!332 = !DILocation(line: 180, column: 19, scope: !306)
!333 = !DILocation(line: 181, column: 24, scope: !331)
!334 = !DILocation(line: 181, column: 13, scope: !331)
!335 = !DILocation(line: 182, column: 19, scope: !336)
!336 = distinct !DILexicalBlock(scope: !331, file: !1, line: 182, column: 19)
!337 = !DILocation(line: 182, column: 19, scope: !331)
!338 = !DILocation(line: 183, column: 27, scope: !336)
!339 = !DILocation(line: 183, column: 13, scope: !336)
!340 = !DILocation(line: 184, column: 19, scope: !341)
!341 = distinct !DILexicalBlock(scope: !336, file: !1, line: 184, column: 19)
!342 = !DILocation(line: 184, column: 19, scope: !336)
!343 = !DILocation(line: 186, column: 19, scope: !344)
!344 = distinct !DILexicalBlock(scope: !341, file: !1, line: 184, column: 51)
!345 = !DILocation(line: 187, column: 29, scope: !344)
!346 = !DILocation(line: 188, column: 11, scope: !344)
!347 = !DILocation(line: 189, column: 11, scope: !258)
!348 = !DILocation(line: 192, column: 15, scope: !234)
!349 = !DILocation(line: 192, column: 13, scope: !234)
!350 = !DILocation(line: 122, column: 7, scope: !351)
!351 = !DILexicalBlockFile(scope: !220, file: !1, discriminator: 4)
!352 = !DILocation(line: 120, column: 5, scope: !353)
!353 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 4)
!354 = !DILocation(line: 120, column: 5, scope: !355)
!355 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 5)
!356 = !DILocation(line: 197, column: 12, scope: !194)
!357 = !DILocation(line: 197, column: 5, scope: !194)
!358 = !DILocation(line: 198, column: 3, scope: !194)
!359 = !DILocation(line: 200, column: 10, scope: !11)
!360 = !DILocation(line: 200, column: 3, scope: !11)
!361 = !DILocation(line: 201, column: 1, scope: !11)
