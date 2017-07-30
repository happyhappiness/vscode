; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_ustar.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.ustar = type { i64, i64, %struct.archive_string_conv*, %struct.archive_string_conv*, i32 }

@.str = private unnamed_addr constant [31 x i8] c"archive_write_set_format_ustar\00", align 1
@.str.1 = private unnamed_addr constant [26 x i8] c"Can't allocate ustar data\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"ustar\00", align 1
@.str.3 = private unnamed_addr constant [12 x i8] c"POSIX ustar\00", align 1
@template_header = internal constant [512 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00000000 \00000000 \00000000 \0000000000000 00000000000         0\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00ustar\0000\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00000000 \00000000 \00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 16
@.str.4 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.5 = private unnamed_addr constant [36 x i8] c"Can't translate pathname '%s' to %s\00", align 1
@.str.6 = private unnamed_addr constant [18 x i8] c"Pathname too long\00", align 1
@.str.7 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Linkname\00", align 1
@.str.8 = private unnamed_addr constant [36 x i8] c"Can't translate linkname '%s' to %s\00", align 1
@.str.9 = private unnamed_addr constant [23 x i8] c"Link contents too long\00", align 1
@.str.10 = private unnamed_addr constant [32 x i8] c"Can't allocate memory for Uname\00", align 1
@.str.11 = private unnamed_addr constant [33 x i8] c"Can't translate uname '%s' to %s\00", align 1
@.str.12 = private unnamed_addr constant [18 x i8] c"Username too long\00", align 1
@.str.13 = private unnamed_addr constant [32 x i8] c"Can't allocate memory for Gname\00", align 1
@.str.14 = private unnamed_addr constant [33 x i8] c"Can't translate gname '%s' to %s\00", align 1
@.str.15 = private unnamed_addr constant [20 x i8] c"Group name too long\00", align 1
@.str.16 = private unnamed_addr constant [23 x i8] c"Numeric mode too large\00", align 1
@.str.17 = private unnamed_addr constant [26 x i8] c"Numeric user ID too large\00", align 1
@.str.18 = private unnamed_addr constant [27 x i8] c"Numeric group ID too large\00", align 1
@.str.19 = private unnamed_addr constant [23 x i8] c"File size out of range\00", align 1
@.str.20 = private unnamed_addr constant [33 x i8] c"File modification time too large\00", align 1
@.str.21 = private unnamed_addr constant [30 x i8] c"Major device number too large\00", align 1
@.str.22 = private unnamed_addr constant [30 x i8] c"Minor device number too large\00", align 1
@.str.23 = private unnamed_addr constant [33 x i8] c"tar format cannot archive socket\00", align 1
@.str.24 = private unnamed_addr constant [43 x i8] c"tar format cannot archive this (mode=0%lo)\00", align 1
@.str.25 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.26 = private unnamed_addr constant [49 x i8] c"%s: hdrcharset option needs a character-set name\00", align 1
@.str.27 = private unnamed_addr constant [48 x i8] c"Can't record entry in tar file without pathname\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_ustar(%struct.archive* %_a) #0 !dbg !205 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %ustar = alloca %struct.ustar*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !230, metadata !231), !dbg !232
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !233, metadata !231), !dbg !234
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !235
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !236
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !234
  call void @llvm.dbg.declare(metadata %struct.ustar** %ustar, metadata !237, metadata !231), !dbg !238
  br label %do.body, !dbg !239

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !240, metadata !231), !dbg !242
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !243
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !243
  store i32 %call, i32* %magic_test, align 4, !dbg !243
  %3 = load i32, i32* %magic_test, align 4, !dbg !243
  %cmp = icmp eq i32 %3, -30, !dbg !243
  br i1 %cmp, label %if.then, label %if.end, !dbg !243

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !245
  br label %return, !dbg !245

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !248

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !250
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !252
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !252
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !253
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !254

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !255
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !256
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !256
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !257
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !258
  br label %if.end5, !dbg !258

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 40) #7, !dbg !259
  %9 = bitcast i8* %call6 to %struct.ustar*, !dbg !260
  store %struct.ustar* %9, %struct.ustar** %ustar, align 8, !dbg !261
  %10 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !262
  %cmp7 = icmp eq %struct.ustar* %10, null, !dbg !264
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !265

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !266
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !268
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !269
  store i32 -30, i32* %retval, align 4, !dbg !270
  br label %return, !dbg !270

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !271
  %13 = bitcast %struct.ustar* %12 to i8*, !dbg !271
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !272
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 14, !dbg !273
  store i8* %13, i8** %format_data, align 8, !dbg !274
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !275
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 15, !dbg !276
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !277
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !278
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 17, !dbg !279
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_ustar_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !280
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !281
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 19, !dbg !282
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_ustar_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !283
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !284
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 20, !dbg !285
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_ustar_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !286
  %19 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !287
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 21, !dbg !288
  store i32 (%struct.archive_write*)* @archive_write_ustar_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !289
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !290
  %format_free10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 22, !dbg !291
  store i32 (%struct.archive_write*)* @archive_write_ustar_free, i32 (%struct.archive_write*)** %format_free10, align 8, !dbg !292
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !293
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 18, !dbg !294
  store i32 (%struct.archive_write*)* @archive_write_ustar_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !295
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !296
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 0, !dbg !297
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !298
  store i32 196609, i32* %archive_format, align 8, !dbg !299
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !300
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !301
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 4, !dbg !302
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !303
  store i32 0, i32* %retval, align 4, !dbg !304
  br label %return, !dbg !304

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !305
  ret i32 %24, !dbg !305
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ustar_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !209 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %ustar = alloca %struct.ustar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !306, metadata !231), !dbg !307
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !308, metadata !231), !dbg !309
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !310, metadata !231), !dbg !311
  call void @llvm.dbg.declare(metadata %struct.ustar** %ustar, metadata !312, metadata !231), !dbg !313
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !314
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !315
  %1 = load i8*, i8** %format_data, align 8, !dbg !315
  %2 = bitcast i8* %1 to %struct.ustar*, !dbg !316
  store %struct.ustar* %2, %struct.ustar** %ustar, align 8, !dbg !313
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !317, metadata !231), !dbg !318
  store i32 -25, i32* %ret, align 4, !dbg !318
  %3 = load i8*, i8** %key.addr, align 8, !dbg !319
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i32 0, i32 0)) #8, !dbg !321
  %cmp = icmp eq i32 %call, 0, !dbg !322
  br i1 %cmp, label %if.then, label %if.end13, !dbg !323

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !324
  %cmp1 = icmp eq i8* %4, null, !dbg !327
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !328

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !329
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !329
  %6 = load i8, i8* %arrayidx, align 1, !dbg !329
  %conv = sext i8 %6 to i32, !dbg !329
  %cmp2 = icmp eq i32 %conv, 0, !dbg !331
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !332

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !333
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !334
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !335
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 15, !dbg !336
  %9 = load i8*, i8** %format_name, align 8, !dbg !336
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.26, i32 0, i32 0), i8* %9), !dbg !337
  br label %if.end12, !dbg !337

if.else:                                          ; preds = %lor.lhs.false
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !338
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !340
  %11 = load i8*, i8** %val.addr, align 8, !dbg !341
  %call6 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive5, i8* %11, i32 0), !dbg !342
  %12 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !343
  %opt_sconv = getelementptr inbounds %struct.ustar, %struct.ustar* %12, i32 0, i32 2, !dbg !344
  store %struct.archive_string_conv* %call6, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !345
  %13 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !346
  %opt_sconv7 = getelementptr inbounds %struct.ustar, %struct.ustar* %13, i32 0, i32 2, !dbg !348
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv7, align 8, !dbg !348
  %cmp8 = icmp ne %struct.archive_string_conv* %14, null, !dbg !349
  br i1 %cmp8, label %if.then10, label %if.else11, !dbg !350

if.then10:                                        ; preds = %if.else
  store i32 0, i32* %ret, align 4, !dbg !351
  br label %if.end, !dbg !352

if.else11:                                        ; preds = %if.else
  store i32 -30, i32* %ret, align 4, !dbg !353
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then10
  br label %if.end12

if.end12:                                         ; preds = %if.end, %if.then4
  %15 = load i32, i32* %ret, align 4, !dbg !354
  store i32 %15, i32* %retval, align 4, !dbg !355
  br label %return, !dbg !355

if.end13:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !356
  br label %return, !dbg !356

return:                                           ; preds = %if.end13, %if.end12
  %16 = load i32, i32* %retval, align 4, !dbg !357
  ret i32 %16, !dbg !357
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ustar_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !210 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %buff = alloca [512 x i8], align 16
  %ret = alloca i32, align 4
  %ret2 = alloca i32, align 4
  %ustar = alloca %struct.ustar*, align 8
  %entry_main = alloca %struct.archive_entry*, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  %p = alloca i8*, align 8
  %path_length = alloca i64, align 8
  %as = alloca %struct.archive_string, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !358, metadata !231), !dbg !359
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !360, metadata !231), !dbg !361
  call void @llvm.dbg.declare(metadata [512 x i8]* %buff, metadata !362, metadata !231), !dbg !364
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !365, metadata !231), !dbg !366
  call void @llvm.dbg.declare(metadata i32* %ret2, metadata !367, metadata !231), !dbg !368
  call void @llvm.dbg.declare(metadata %struct.ustar** %ustar, metadata !369, metadata !231), !dbg !370
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry_main, metadata !371, metadata !231), !dbg !372
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !373, metadata !231), !dbg !374
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !375
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !376
  %1 = load i8*, i8** %format_data, align 8, !dbg !376
  %2 = bitcast i8* %1 to %struct.ustar*, !dbg !377
  store %struct.ustar* %2, %struct.ustar** %ustar, align 8, !dbg !378
  %3 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !379
  %opt_sconv = getelementptr inbounds %struct.ustar, %struct.ustar* %3, i32 0, i32 2, !dbg !381
  %4 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !381
  %cmp = icmp eq %struct.archive_string_conv* %4, null, !dbg !382
  br i1 %cmp, label %if.then, label %if.else, !dbg !383

if.then:                                          ; preds = %entry
  %5 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !384
  %init_default_conversion = getelementptr inbounds %struct.ustar, %struct.ustar* %5, i32 0, i32 4, !dbg !387
  %6 = load i32, i32* %init_default_conversion, align 8, !dbg !387
  %tobool = icmp ne i32 %6, 0, !dbg !384
  br i1 %tobool, label %if.end, label %if.then2, !dbg !388

if.then2:                                         ; preds = %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !389
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !391
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive* %archive), !dbg !392
  %8 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !393
  %sconv_default = getelementptr inbounds %struct.ustar, %struct.ustar* %8, i32 0, i32 3, !dbg !394
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !395
  %9 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !396
  %init_default_conversion3 = getelementptr inbounds %struct.ustar, %struct.ustar* %9, i32 0, i32 4, !dbg !397
  store i32 1, i32* %init_default_conversion3, align 8, !dbg !398
  br label %if.end, !dbg !399

if.end:                                           ; preds = %if.then2, %if.then
  %10 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !400
  %sconv_default4 = getelementptr inbounds %struct.ustar, %struct.ustar* %10, i32 0, i32 3, !dbg !401
  %11 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default4, align 8, !dbg !401
  store %struct.archive_string_conv* %11, %struct.archive_string_conv** %sconv, align 8, !dbg !402
  br label %if.end6, !dbg !403

if.else:                                          ; preds = %entry
  %12 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !404
  %opt_sconv5 = getelementptr inbounds %struct.ustar, %struct.ustar* %12, i32 0, i32 2, !dbg !405
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv5, align 8, !dbg !405
  store %struct.archive_string_conv* %13, %struct.archive_string_conv** %sconv, align 8, !dbg !406
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.end
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !407
  %call7 = call i8* @archive_entry_pathname(%struct.archive_entry* %14), !dbg !409
  %cmp8 = icmp eq i8* %call7, null, !dbg !410
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !411

if.then9:                                         ; preds = %if.end6
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !412
  %archive10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 0, !dbg !414
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.27, i32 0, i32 0)), !dbg !415
  store i32 -25, i32* %retval, align 4, !dbg !416
  br label %return, !dbg !416

if.end11:                                         ; preds = %if.end6
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !417
  %call12 = call i8* @archive_entry_hardlink(%struct.archive_entry* %16), !dbg !419
  %cmp13 = icmp ne i8* %call12, null, !dbg !420
  br i1 %cmp13, label %if.then19, label %lor.lhs.false, !dbg !421

lor.lhs.false:                                    ; preds = %if.end11
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !422
  %call14 = call i8* @archive_entry_symlink(%struct.archive_entry* %17), !dbg !423
  %cmp15 = icmp ne i8* %call14, null, !dbg !424
  br i1 %cmp15, label %if.then19, label %lor.lhs.false16, !dbg !425

lor.lhs.false16:                                  ; preds = %lor.lhs.false
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !426
  %call17 = call i32 @archive_entry_filetype(%struct.archive_entry* %18), !dbg !427
  %cmp18 = icmp eq i32 %call17, 32768, !dbg !428
  br i1 %cmp18, label %if.end20, label %if.then19, !dbg !429

if.then19:                                        ; preds = %lor.lhs.false16, %lor.lhs.false, %if.end11
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !431
  call void @archive_entry_set_size(%struct.archive_entry* %19, i64 0), !dbg !432
  br label %if.end20, !dbg !432

if.end20:                                         ; preds = %if.then19, %lor.lhs.false16
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !433
  %call21 = call i32 @archive_entry_filetype(%struct.archive_entry* %20), !dbg !435
  %cmp22 = icmp eq i32 16384, %call21, !dbg !436
  br i1 %cmp22, label %if.then23, label %if.end47, !dbg !437

if.then23:                                        ; preds = %if.end20
  call void @llvm.dbg.declare(metadata i8** %p, metadata !438, metadata !231), !dbg !440
  call void @llvm.dbg.declare(metadata i64* %path_length, metadata !441, metadata !231), !dbg !442
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !443
  %call24 = call i8* @archive_entry_pathname(%struct.archive_entry* %21), !dbg !444
  store i8* %call24, i8** %p, align 8, !dbg !445
  %22 = load i8*, i8** %p, align 8, !dbg !446
  %cmp25 = icmp ne i8* %22, null, !dbg !448
  br i1 %cmp25, label %land.lhs.true, label %if.end46, !dbg !449

land.lhs.true:                                    ; preds = %if.then23
  %23 = load i8*, i8** %p, align 8, !dbg !450
  %arrayidx = getelementptr inbounds i8, i8* %23, i64 0, !dbg !450
  %24 = load i8, i8* %arrayidx, align 1, !dbg !450
  %conv = sext i8 %24 to i32, !dbg !450
  %cmp26 = icmp ne i32 %conv, 0, !dbg !452
  br i1 %cmp26, label %land.lhs.true28, label %if.end46, !dbg !453

land.lhs.true28:                                  ; preds = %land.lhs.true
  %25 = load i8*, i8** %p, align 8, !dbg !454
  %call29 = call i64 @strlen(i8* %25) #8, !dbg !456
  %sub = sub i64 %call29, 1, !dbg !457
  %26 = load i8*, i8** %p, align 8, !dbg !458
  %arrayidx30 = getelementptr inbounds i8, i8* %26, i64 %sub, !dbg !458
  %27 = load i8, i8* %arrayidx30, align 1, !dbg !458
  %conv31 = sext i8 %27 to i32, !dbg !458
  %cmp32 = icmp ne i32 %conv31, 47, !dbg !459
  br i1 %cmp32, label %if.then34, label %if.end46, !dbg !460

if.then34:                                        ; preds = %land.lhs.true28
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !461, metadata !231), !dbg !463
  br label %do.body, !dbg !464

do.body:                                          ; preds = %if.then34
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !465
  store i8* null, i8** %s, align 8, !dbg !465
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !465
  store i64 0, i64* %length, align 8, !dbg !465
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !465
  store i64 0, i64* %buffer_length, align 8, !dbg !465
  br label %do.end, !dbg !465

do.end:                                           ; preds = %do.body
  %28 = load i8*, i8** %p, align 8, !dbg !468
  %call35 = call i64 @strlen(i8* %28) #8, !dbg !469
  store i64 %call35, i64* %path_length, align 8, !dbg !470
  %29 = load i64, i64* %path_length, align 8, !dbg !471
  %add = add i64 %29, 2, !dbg !473
  %call36 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %as, i64 %add), !dbg !474
  %cmp37 = icmp eq %struct.archive_string* %call36, null, !dbg !475
  br i1 %cmp37, label %if.then39, label %if.end41, !dbg !476

if.then39:                                        ; preds = %do.end
  %30 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !477
  %archive40 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %30, i32 0, i32 0, !dbg !479
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive40, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !480
  call void @archive_string_free(%struct.archive_string* %as), !dbg !481
  store i32 -30, i32* %retval, align 4, !dbg !482
  br label %return, !dbg !482

if.end41:                                         ; preds = %do.end
  %length42 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !483
  store i64 0, i64* %length42, align 8, !dbg !483
  %31 = load i8*, i8** %p, align 8, !dbg !483
  %32 = load i64, i64* %path_length, align 8, !dbg !483
  %call43 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %31, i64 %32), !dbg !483
  %call44 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext 47), !dbg !484
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !485
  %s45 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !486
  %34 = load i8*, i8** %s45, align 8, !dbg !486
  call void @archive_entry_copy_pathname(%struct.archive_entry* %33, i8* %34), !dbg !487
  call void @archive_string_free(%struct.archive_string* %as), !dbg !488
  br label %if.end46, !dbg !489

if.end46:                                         ; preds = %if.end41, %land.lhs.true28, %land.lhs.true, %if.then23
  br label %if.end47, !dbg !490

if.end47:                                         ; preds = %if.end46, %if.end20
  store %struct.archive_entry* null, %struct.archive_entry** %entry_main, align 8, !dbg !491
  %35 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !492
  %arraydecay = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !493
  %36 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !494
  %37 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !495
  %call48 = call i32 @__archive_write_format_header_ustar(%struct.archive_write* %35, i8* %arraydecay, %struct.archive_entry* %36, i32 -1, i32 1, %struct.archive_string_conv* %37), !dbg !496
  store i32 %call48, i32* %ret, align 4, !dbg !497
  %38 = load i32, i32* %ret, align 4, !dbg !498
  %cmp49 = icmp slt i32 %38, -20, !dbg !500
  br i1 %cmp49, label %if.then51, label %if.end55, !dbg !501

if.then51:                                        ; preds = %if.end47
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !502
  %tobool52 = icmp ne %struct.archive_entry* %39, null, !dbg !502
  br i1 %tobool52, label %if.then53, label %if.end54, !dbg !505

if.then53:                                        ; preds = %if.then51
  %40 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !506
  call void @archive_entry_free(%struct.archive_entry* %40), !dbg !507
  br label %if.end54, !dbg !507

if.end54:                                         ; preds = %if.then53, %if.then51
  %41 = load i32, i32* %ret, align 4, !dbg !508
  store i32 %41, i32* %retval, align 4, !dbg !509
  br label %return, !dbg !509

if.end55:                                         ; preds = %if.end47
  %42 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !510
  %arraydecay56 = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !511
  %call57 = call i32 @__archive_write_output(%struct.archive_write* %42, i8* %arraydecay56, i64 512), !dbg !512
  store i32 %call57, i32* %ret2, align 4, !dbg !513
  %43 = load i32, i32* %ret2, align 4, !dbg !514
  %cmp58 = icmp slt i32 %43, -20, !dbg !516
  br i1 %cmp58, label %if.then60, label %if.end64, !dbg !517

if.then60:                                        ; preds = %if.end55
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !518
  %tobool61 = icmp ne %struct.archive_entry* %44, null, !dbg !518
  br i1 %tobool61, label %if.then62, label %if.end63, !dbg !521

if.then62:                                        ; preds = %if.then60
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !522
  call void @archive_entry_free(%struct.archive_entry* %45), !dbg !523
  br label %if.end63, !dbg !523

if.end63:                                         ; preds = %if.then62, %if.then60
  %46 = load i32, i32* %ret2, align 4, !dbg !524
  store i32 %46, i32* %retval, align 4, !dbg !525
  br label %return, !dbg !525

if.end64:                                         ; preds = %if.end55
  %47 = load i32, i32* %ret2, align 4, !dbg !526
  %48 = load i32, i32* %ret, align 4, !dbg !528
  %cmp65 = icmp slt i32 %47, %48, !dbg !529
  br i1 %cmp65, label %if.then67, label %if.end68, !dbg !530

if.then67:                                        ; preds = %if.end64
  %49 = load i32, i32* %ret2, align 4, !dbg !531
  store i32 %49, i32* %ret, align 4, !dbg !532
  br label %if.end68, !dbg !533

if.end68:                                         ; preds = %if.then67, %if.end64
  %50 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !534
  %call69 = call i64 @archive_entry_size(%struct.archive_entry* %50), !dbg !535
  %51 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !536
  %entry_bytes_remaining = getelementptr inbounds %struct.ustar, %struct.ustar* %51, i32 0, i32 0, !dbg !537
  store i64 %call69, i64* %entry_bytes_remaining, align 8, !dbg !538
  %52 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !539
  %entry_bytes_remaining70 = getelementptr inbounds %struct.ustar, %struct.ustar* %52, i32 0, i32 0, !dbg !540
  %53 = load i64, i64* %entry_bytes_remaining70, align 8, !dbg !540
  %sub71 = sub nsw i64 0, %53, !dbg !541
  %and = and i64 511, %sub71, !dbg !542
  %54 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !543
  %entry_padding = getelementptr inbounds %struct.ustar, %struct.ustar* %54, i32 0, i32 1, !dbg !544
  store i64 %and, i64* %entry_padding, align 8, !dbg !545
  %55 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !546
  %tobool72 = icmp ne %struct.archive_entry* %55, null, !dbg !546
  br i1 %tobool72, label %if.then73, label %if.end74, !dbg !548

if.then73:                                        ; preds = %if.end68
  %56 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !549
  call void @archive_entry_free(%struct.archive_entry* %56), !dbg !550
  br label %if.end74, !dbg !550

if.end74:                                         ; preds = %if.then73, %if.end68
  %57 = load i32, i32* %ret, align 4, !dbg !551
  store i32 %57, i32* %retval, align 4, !dbg !552
  br label %return, !dbg !552

return:                                           ; preds = %if.end74, %if.end63, %if.end54, %if.then39, %if.then9
  %58 = load i32, i32* %retval, align 4, !dbg !553
  ret i32 %58, !dbg !553
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_ustar_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !221 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %ustar = alloca %struct.ustar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !554, metadata !231), !dbg !555
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !556, metadata !231), !dbg !557
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !558, metadata !231), !dbg !559
  call void @llvm.dbg.declare(metadata %struct.ustar** %ustar, metadata !560, metadata !231), !dbg !561
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !562, metadata !231), !dbg !563
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !564
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !565
  %1 = load i8*, i8** %format_data, align 8, !dbg !565
  %2 = bitcast i8* %1 to %struct.ustar*, !dbg !566
  store %struct.ustar* %2, %struct.ustar** %ustar, align 8, !dbg !567
  %3 = load i64, i64* %s.addr, align 8, !dbg !568
  %4 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !570
  %entry_bytes_remaining = getelementptr inbounds %struct.ustar, %struct.ustar* %4, i32 0, i32 0, !dbg !571
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !571
  %cmp = icmp ugt i64 %3, %5, !dbg !572
  br i1 %cmp, label %if.then, label %if.end, !dbg !573

if.then:                                          ; preds = %entry
  %6 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !574
  %entry_bytes_remaining1 = getelementptr inbounds %struct.ustar, %struct.ustar* %6, i32 0, i32 0, !dbg !575
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !575
  store i64 %7, i64* %s.addr, align 8, !dbg !576
  br label %if.end, !dbg !577

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !578
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !579
  %10 = load i64, i64* %s.addr, align 8, !dbg !580
  %call = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %9, i64 %10), !dbg !581
  store i32 %call, i32* %ret, align 4, !dbg !582
  %11 = load i64, i64* %s.addr, align 8, !dbg !583
  %12 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !584
  %entry_bytes_remaining2 = getelementptr inbounds %struct.ustar, %struct.ustar* %12, i32 0, i32 0, !dbg !585
  %13 = load i64, i64* %entry_bytes_remaining2, align 8, !dbg !586
  %sub = sub i64 %13, %11, !dbg !586
  store i64 %sub, i64* %entry_bytes_remaining2, align 8, !dbg !586
  %14 = load i32, i32* %ret, align 4, !dbg !587
  %cmp3 = icmp ne i32 %14, 0, !dbg !589
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !590

if.then4:                                         ; preds = %if.end
  %15 = load i32, i32* %ret, align 4, !dbg !591
  %conv = sext i32 %15 to i64, !dbg !592
  store i64 %conv, i64* %retval, align 8, !dbg !593
  br label %return, !dbg !593

if.end5:                                          ; preds = %if.end
  %16 = load i64, i64* %s.addr, align 8, !dbg !594
  store i64 %16, i64* %retval, align 8, !dbg !595
  br label %return, !dbg !595

return:                                           ; preds = %if.end5, %if.then4
  %17 = load i64, i64* %retval, align 8, !dbg !596
  ret i64 %17, !dbg !596
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ustar_close(%struct.archive_write* %a) #0 !dbg !218 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !597, metadata !231), !dbg !598
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !599
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %0, i64 1024), !dbg !600
  ret i32 %call, !dbg !601
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ustar_free(%struct.archive_write* %a) #0 !dbg !219 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %ustar = alloca %struct.ustar*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !602, metadata !231), !dbg !603
  call void @llvm.dbg.declare(metadata %struct.ustar** %ustar, metadata !604, metadata !231), !dbg !605
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !606
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !607
  %1 = load i8*, i8** %format_data, align 8, !dbg !607
  %2 = bitcast i8* %1 to %struct.ustar*, !dbg !608
  store %struct.ustar* %2, %struct.ustar** %ustar, align 8, !dbg !609
  %3 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !610
  %4 = bitcast %struct.ustar* %3 to i8*, !dbg !610
  call void @free(i8* %4) #7, !dbg !611
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !612
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 14, !dbg !613
  store i8* null, i8** %format_data1, align 8, !dbg !614
  ret i32 0, !dbg !615
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ustar_finish_entry(%struct.archive_write* %a) #0 !dbg !220 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %ustar = alloca %struct.ustar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !616, metadata !231), !dbg !617
  call void @llvm.dbg.declare(metadata %struct.ustar** %ustar, metadata !618, metadata !231), !dbg !619
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !620, metadata !231), !dbg !621
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !622
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !623
  %1 = load i8*, i8** %format_data, align 8, !dbg !623
  %2 = bitcast i8* %1 to %struct.ustar*, !dbg !624
  store %struct.ustar* %2, %struct.ustar** %ustar, align 8, !dbg !625
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !626
  %4 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !627
  %entry_bytes_remaining = getelementptr inbounds %struct.ustar, %struct.ustar* %4, i32 0, i32 0, !dbg !628
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !628
  %6 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !629
  %entry_padding = getelementptr inbounds %struct.ustar, %struct.ustar* %6, i32 0, i32 1, !dbg !630
  %7 = load i64, i64* %entry_padding, align 8, !dbg !630
  %add = add i64 %5, %7, !dbg !631
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %3, i64 %add), !dbg !632
  store i32 %call, i32* %ret, align 4, !dbg !633
  %8 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !634
  %entry_padding1 = getelementptr inbounds %struct.ustar, %struct.ustar* %8, i32 0, i32 1, !dbg !635
  store i64 0, i64* %entry_padding1, align 8, !dbg !636
  %9 = load %struct.ustar*, %struct.ustar** %ustar, align 8, !dbg !637
  %entry_bytes_remaining2 = getelementptr inbounds %struct.ustar, %struct.ustar* %9, i32 0, i32 0, !dbg !638
  store i64 0, i64* %entry_bytes_remaining2, align 8, !dbg !639
  %10 = load i32, i32* %ret, align 4, !dbg !640
  ret i32 %10, !dbg !641
}

; Function Attrs: nounwind uwtable
define i32 @__archive_write_format_header_ustar(%struct.archive_write* %a, i8* %h, %struct.archive_entry* %entry1, i32 %tartype, i32 %strict, %struct.archive_string_conv* %sconv) #0 !dbg !206 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %h.addr = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %tartype.addr = alloca i32, align 4
  %strict.addr = alloca i32, align 4
  %sconv.addr = alloca %struct.archive_string_conv*, align 8
  %checksum = alloca i32, align 4
  %i = alloca i32, align 4
  %r = alloca i32, align 4
  %ret = alloca i32, align 4
  %copy_length = alloca i64, align 8
  %p = alloca i8*, align 8
  %pp = alloca i8*, align 8
  %mytartype = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !642, metadata !231), !dbg !643
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !644, metadata !231), !dbg !645
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !646, metadata !231), !dbg !647
  store i32 %tartype, i32* %tartype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tartype.addr, metadata !648, metadata !231), !dbg !649
  store i32 %strict, i32* %strict.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %strict.addr, metadata !650, metadata !231), !dbg !651
  store %struct.archive_string_conv* %sconv, %struct.archive_string_conv** %sconv.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv.addr, metadata !652, metadata !231), !dbg !653
  call void @llvm.dbg.declare(metadata i32* %checksum, metadata !654, metadata !231), !dbg !655
  call void @llvm.dbg.declare(metadata i32* %i, metadata !656, metadata !231), !dbg !657
  call void @llvm.dbg.declare(metadata i32* %r, metadata !658, metadata !231), !dbg !659
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !660, metadata !231), !dbg !661
  call void @llvm.dbg.declare(metadata i64* %copy_length, metadata !662, metadata !231), !dbg !663
  call void @llvm.dbg.declare(metadata i8** %p, metadata !664, metadata !231), !dbg !665
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !666, metadata !231), !dbg !667
  call void @llvm.dbg.declare(metadata i32* %mytartype, metadata !668, metadata !231), !dbg !669
  store i32 0, i32* %ret, align 4, !dbg !670
  store i32 -1, i32* %mytartype, align 4, !dbg !671
  %0 = load i8*, i8** %h.addr, align 8, !dbg !672
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* getelementptr inbounds ([512 x i8], [512 x i8]* @template_header, i32 0, i32 0), i64 512, i32 1, i1 false), !dbg !673
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !674
  %2 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !675
  %call = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %1, i8** %pp, i64* %copy_length, %struct.archive_string_conv* %2), !dbg !676
  store i32 %call, i32* %r, align 4, !dbg !677
  %3 = load i32, i32* %r, align 4, !dbg !678
  %cmp = icmp ne i32 %3, 0, !dbg !680
  br i1 %cmp, label %if.then, label %if.end7, !dbg !681

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !682
  %4 = load i32, i32* %call2, align 4, !dbg !682
  %cmp3 = icmp eq i32 %4, 12, !dbg !685
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !686

if.then4:                                         ; preds = %if.then
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !687
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !689
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.4, i32 0, i32 0)), !dbg !690
  store i32 -30, i32* %retval, align 4, !dbg !691
  br label %return, !dbg !691

if.end:                                           ; preds = %if.then
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !692
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !693
  %7 = load i8*, i8** %pp, align 8, !dbg !694
  %8 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !695
  %call6 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %8), !dbg !696
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive5, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.5, i32 0, i32 0), i8* %7, i8* %call6), !dbg !697
  store i32 -20, i32* %ret, align 4, !dbg !698
  br label %if.end7, !dbg !699

if.end7:                                          ; preds = %if.end, %entry
  %9 = load i64, i64* %copy_length, align 8, !dbg !700
  %cmp8 = icmp ule i64 %9, 100, !dbg !702
  br i1 %cmp8, label %if.then9, label %if.else, !dbg !703

if.then9:                                         ; preds = %if.end7
  %10 = load i8*, i8** %h.addr, align 8, !dbg !704
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 0, !dbg !705
  %11 = load i8*, i8** %pp, align 8, !dbg !706
  %12 = load i64, i64* %copy_length, align 8, !dbg !707
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %11, i64 %12, i32 1, i1 false), !dbg !708
  br label %if.end43, !dbg !708

if.else:                                          ; preds = %if.end7
  %13 = load i8*, i8** %pp, align 8, !dbg !709
  %14 = load i64, i64* %copy_length, align 8, !dbg !711
  %add.ptr10 = getelementptr inbounds i8, i8* %13, i64 %14, !dbg !712
  %add.ptr11 = getelementptr inbounds i8, i8* %add.ptr10, i64 -100, !dbg !713
  %add.ptr12 = getelementptr inbounds i8, i8* %add.ptr11, i64 -1, !dbg !714
  %call13 = call i8* @strchr(i8* %add.ptr12, i32 47) #8, !dbg !715
  store i8* %call13, i8** %p, align 8, !dbg !716
  %15 = load i8*, i8** %p, align 8, !dbg !717
  %16 = load i8*, i8** %pp, align 8, !dbg !719
  %cmp14 = icmp eq i8* %15, %16, !dbg !720
  br i1 %cmp14, label %if.then15, label %if.end18, !dbg !721

if.then15:                                        ; preds = %if.else
  %17 = load i8*, i8** %p, align 8, !dbg !722
  %add.ptr16 = getelementptr inbounds i8, i8* %17, i64 1, !dbg !723
  %call17 = call i8* @strchr(i8* %add.ptr16, i32 47) #8, !dbg !724
  store i8* %call17, i8** %p, align 8, !dbg !725
  br label %if.end18, !dbg !726

if.end18:                                         ; preds = %if.then15, %if.else
  %18 = load i8*, i8** %p, align 8, !dbg !727
  %tobool = icmp ne i8* %18, null, !dbg !727
  br i1 %tobool, label %if.else21, label %if.then19, !dbg !729

if.then19:                                        ; preds = %if.end18
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !730
  %archive20 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 0, !dbg !732
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive20, i32 36, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i32 0, i32 0)), !dbg !733
  store i32 -25, i32* %ret, align 4, !dbg !734
  br label %if.end42, !dbg !735

if.else21:                                        ; preds = %if.end18
  %20 = load i8*, i8** %p, align 8, !dbg !736
  %arrayidx = getelementptr inbounds i8, i8* %20, i64 1, !dbg !736
  %21 = load i8, i8* %arrayidx, align 1, !dbg !736
  %conv = sext i8 %21 to i32, !dbg !736
  %cmp22 = icmp eq i32 %conv, 0, !dbg !739
  br i1 %cmp22, label %if.then24, label %if.else26, !dbg !736

if.then24:                                        ; preds = %if.else21
  %22 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !740
  %archive25 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 0, !dbg !742
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 36, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i32 0, i32 0)), !dbg !743
  store i32 -25, i32* %ret, align 4, !dbg !744
  br label %if.end41, !dbg !745

if.else26:                                        ; preds = %if.else21
  %23 = load i8*, i8** %p, align 8, !dbg !746
  %24 = load i8*, i8** %pp, align 8, !dbg !749
  %add.ptr27 = getelementptr inbounds i8, i8* %24, i64 155, !dbg !750
  %cmp28 = icmp ugt i8* %23, %add.ptr27, !dbg !751
  br i1 %cmp28, label %if.then30, label %if.else32, !dbg !746

if.then30:                                        ; preds = %if.else26
  %25 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !752
  %archive31 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 0, !dbg !754
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive31, i32 36, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i32 0, i32 0)), !dbg !755
  store i32 -25, i32* %ret, align 4, !dbg !756
  br label %if.end40, !dbg !757

if.else32:                                        ; preds = %if.else26
  %26 = load i8*, i8** %h.addr, align 8, !dbg !758
  %add.ptr33 = getelementptr inbounds i8, i8* %26, i64 345, !dbg !760
  %27 = load i8*, i8** %pp, align 8, !dbg !761
  %28 = load i8*, i8** %p, align 8, !dbg !762
  %29 = load i8*, i8** %pp, align 8, !dbg !763
  %sub.ptr.lhs.cast = ptrtoint i8* %28 to i64, !dbg !764
  %sub.ptr.rhs.cast = ptrtoint i8* %29 to i64, !dbg !764
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !764
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr33, i8* %27, i64 %sub.ptr.sub, i32 1, i1 false), !dbg !765
  %30 = load i8*, i8** %h.addr, align 8, !dbg !766
  %add.ptr34 = getelementptr inbounds i8, i8* %30, i64 0, !dbg !767
  %31 = load i8*, i8** %p, align 8, !dbg !768
  %add.ptr35 = getelementptr inbounds i8, i8* %31, i64 1, !dbg !769
  %32 = load i8*, i8** %pp, align 8, !dbg !770
  %33 = load i64, i64* %copy_length, align 8, !dbg !771
  %add.ptr36 = getelementptr inbounds i8, i8* %32, i64 %33, !dbg !772
  %34 = load i8*, i8** %p, align 8, !dbg !773
  %sub.ptr.lhs.cast37 = ptrtoint i8* %add.ptr36 to i64, !dbg !774
  %sub.ptr.rhs.cast38 = ptrtoint i8* %34 to i64, !dbg !774
  %sub.ptr.sub39 = sub i64 %sub.ptr.lhs.cast37, %sub.ptr.rhs.cast38, !dbg !774
  %sub = sub nsw i64 %sub.ptr.sub39, 1, !dbg !775
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr34, i8* %add.ptr35, i64 %sub, i32 1, i1 false), !dbg !776
  br label %if.end40

if.end40:                                         ; preds = %if.else32, %if.then30
  br label %if.end41

if.end41:                                         ; preds = %if.end40, %if.then24
  br label %if.end42

if.end42:                                         ; preds = %if.end41, %if.then19
  br label %if.end43

if.end43:                                         ; preds = %if.end42, %if.then9
  %35 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !777
  %36 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !778
  %call44 = call i32 @_archive_entry_hardlink_l(%struct.archive_entry* %35, i8** %p, i64* %copy_length, %struct.archive_string_conv* %36), !dbg !779
  store i32 %call44, i32* %r, align 4, !dbg !780
  %37 = load i32, i32* %r, align 4, !dbg !781
  %cmp45 = icmp ne i32 %37, 0, !dbg !783
  br i1 %cmp45, label %if.then47, label %if.end56, !dbg !784

if.then47:                                        ; preds = %if.end43
  %call48 = call i32* @__errno_location() #1, !dbg !785
  %38 = load i32, i32* %call48, align 4, !dbg !785
  %cmp49 = icmp eq i32 %38, 12, !dbg !788
  br i1 %cmp49, label %if.then51, label %if.end53, !dbg !789

if.then51:                                        ; preds = %if.then47
  %39 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !790
  %archive52 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %39, i32 0, i32 0, !dbg !792
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive52, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.7, i32 0, i32 0)), !dbg !793
  store i32 -30, i32* %retval, align 4, !dbg !794
  br label %return, !dbg !794

if.end53:                                         ; preds = %if.then47
  %40 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !795
  %archive54 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %40, i32 0, i32 0, !dbg !796
  %41 = load i8*, i8** %p, align 8, !dbg !797
  %42 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !798
  %call55 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %42), !dbg !799
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive54, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.8, i32 0, i32 0), i8* %41, i8* %call55), !dbg !800
  store i32 -20, i32* %ret, align 4, !dbg !801
  br label %if.end56, !dbg !802

if.end56:                                         ; preds = %if.end53, %if.end43
  %43 = load i64, i64* %copy_length, align 8, !dbg !803
  %cmp57 = icmp ugt i64 %43, 0, !dbg !805
  br i1 %cmp57, label %if.then59, label %if.else60, !dbg !806

if.then59:                                        ; preds = %if.end56
  store i32 49, i32* %mytartype, align 4, !dbg !807
  br label %if.end74, !dbg !808

if.else60:                                        ; preds = %if.end56
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !809
  %45 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !811
  %call61 = call i32 @_archive_entry_symlink_l(%struct.archive_entry* %44, i8** %p, i64* %copy_length, %struct.archive_string_conv* %45), !dbg !812
  store i32 %call61, i32* %r, align 4, !dbg !813
  %46 = load i32, i32* %r, align 4, !dbg !814
  %cmp62 = icmp ne i32 %46, 0, !dbg !816
  br i1 %cmp62, label %if.then64, label %if.end73, !dbg !817

if.then64:                                        ; preds = %if.else60
  %call65 = call i32* @__errno_location() #1, !dbg !818
  %47 = load i32, i32* %call65, align 4, !dbg !818
  %cmp66 = icmp eq i32 %47, 12, !dbg !821
  br i1 %cmp66, label %if.then68, label %if.end70, !dbg !822

if.then68:                                        ; preds = %if.then64
  %48 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !823
  %archive69 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %48, i32 0, i32 0, !dbg !825
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive69, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.7, i32 0, i32 0)), !dbg !826
  store i32 -30, i32* %retval, align 4, !dbg !827
  br label %return, !dbg !827

if.end70:                                         ; preds = %if.then64
  %49 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !828
  %archive71 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %49, i32 0, i32 0, !dbg !829
  %50 = load i8*, i8** %p, align 8, !dbg !830
  %51 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !831
  %call72 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %51), !dbg !832
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive71, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.8, i32 0, i32 0), i8* %50, i8* %call72), !dbg !833
  store i32 -20, i32* %ret, align 4, !dbg !834
  br label %if.end73, !dbg !835

if.end73:                                         ; preds = %if.end70, %if.else60
  br label %if.end74

if.end74:                                         ; preds = %if.end73, %if.then59
  %52 = load i64, i64* %copy_length, align 8, !dbg !836
  %cmp75 = icmp ugt i64 %52, 0, !dbg !838
  br i1 %cmp75, label %if.then77, label %if.end84, !dbg !839

if.then77:                                        ; preds = %if.end74
  %53 = load i64, i64* %copy_length, align 8, !dbg !840
  %cmp78 = icmp ugt i64 %53, 100, !dbg !843
  br i1 %cmp78, label %if.then80, label %if.end82, !dbg !844

if.then80:                                        ; preds = %if.then77
  %54 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !845
  %archive81 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %54, i32 0, i32 0, !dbg !847
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive81, i32 36, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.9, i32 0, i32 0)), !dbg !848
  store i32 -25, i32* %ret, align 4, !dbg !849
  store i64 100, i64* %copy_length, align 8, !dbg !850
  br label %if.end82, !dbg !851

if.end82:                                         ; preds = %if.then80, %if.then77
  %55 = load i8*, i8** %h.addr, align 8, !dbg !852
  %add.ptr83 = getelementptr inbounds i8, i8* %55, i64 157, !dbg !853
  %56 = load i8*, i8** %p, align 8, !dbg !854
  %57 = load i64, i64* %copy_length, align 8, !dbg !855
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr83, i8* %56, i64 %57, i32 1, i1 false), !dbg !856
  br label %if.end84, !dbg !857

if.end84:                                         ; preds = %if.end82, %if.end74
  %58 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !858
  %59 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !859
  %call85 = call i32 @_archive_entry_uname_l(%struct.archive_entry* %58, i8** %p, i64* %copy_length, %struct.archive_string_conv* %59), !dbg !860
  store i32 %call85, i32* %r, align 4, !dbg !861
  %60 = load i32, i32* %r, align 4, !dbg !862
  %cmp86 = icmp ne i32 %60, 0, !dbg !864
  br i1 %cmp86, label %if.then88, label %if.end97, !dbg !865

if.then88:                                        ; preds = %if.end84
  %call89 = call i32* @__errno_location() #1, !dbg !866
  %61 = load i32, i32* %call89, align 4, !dbg !866
  %cmp90 = icmp eq i32 %61, 12, !dbg !869
  br i1 %cmp90, label %if.then92, label %if.end94, !dbg !870

if.then92:                                        ; preds = %if.then88
  %62 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !871
  %archive93 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %62, i32 0, i32 0, !dbg !873
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive93, i32 12, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.10, i32 0, i32 0)), !dbg !874
  store i32 -30, i32* %retval, align 4, !dbg !875
  br label %return, !dbg !875

if.end94:                                         ; preds = %if.then88
  %63 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !876
  %archive95 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %63, i32 0, i32 0, !dbg !877
  %64 = load i8*, i8** %p, align 8, !dbg !878
  %65 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !879
  %call96 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %65), !dbg !880
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive95, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.11, i32 0, i32 0), i8* %64, i8* %call96), !dbg !881
  store i32 -20, i32* %ret, align 4, !dbg !882
  br label %if.end97, !dbg !883

if.end97:                                         ; preds = %if.end94, %if.end84
  %66 = load i64, i64* %copy_length, align 8, !dbg !884
  %cmp98 = icmp ugt i64 %66, 0, !dbg !886
  br i1 %cmp98, label %if.then100, label %if.end107, !dbg !887

if.then100:                                       ; preds = %if.end97
  %67 = load i64, i64* %copy_length, align 8, !dbg !888
  %cmp101 = icmp ugt i64 %67, 32, !dbg !891
  br i1 %cmp101, label %if.then103, label %if.end105, !dbg !892

if.then103:                                       ; preds = %if.then100
  %68 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !893
  %archive104 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %68, i32 0, i32 0, !dbg !895
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive104, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.12, i32 0, i32 0)), !dbg !896
  store i32 -25, i32* %ret, align 4, !dbg !897
  store i64 32, i64* %copy_length, align 8, !dbg !898
  br label %if.end105, !dbg !899

if.end105:                                        ; preds = %if.then103, %if.then100
  %69 = load i8*, i8** %h.addr, align 8, !dbg !900
  %add.ptr106 = getelementptr inbounds i8, i8* %69, i64 265, !dbg !901
  %70 = load i8*, i8** %p, align 8, !dbg !902
  %71 = load i64, i64* %copy_length, align 8, !dbg !903
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr106, i8* %70, i64 %71, i32 1, i1 false), !dbg !904
  br label %if.end107, !dbg !905

if.end107:                                        ; preds = %if.end105, %if.end97
  %72 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !906
  %73 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !907
  %call108 = call i32 @_archive_entry_gname_l(%struct.archive_entry* %72, i8** %p, i64* %copy_length, %struct.archive_string_conv* %73), !dbg !908
  store i32 %call108, i32* %r, align 4, !dbg !909
  %74 = load i32, i32* %r, align 4, !dbg !910
  %cmp109 = icmp ne i32 %74, 0, !dbg !912
  br i1 %cmp109, label %if.then111, label %if.end120, !dbg !913

if.then111:                                       ; preds = %if.end107
  %call112 = call i32* @__errno_location() #1, !dbg !914
  %75 = load i32, i32* %call112, align 4, !dbg !914
  %cmp113 = icmp eq i32 %75, 12, !dbg !917
  br i1 %cmp113, label %if.then115, label %if.end117, !dbg !918

if.then115:                                       ; preds = %if.then111
  %76 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !919
  %archive116 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %76, i32 0, i32 0, !dbg !921
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive116, i32 12, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.13, i32 0, i32 0)), !dbg !922
  store i32 -30, i32* %retval, align 4, !dbg !923
  br label %return, !dbg !923

if.end117:                                        ; preds = %if.then111
  %77 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !924
  %archive118 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %77, i32 0, i32 0, !dbg !925
  %78 = load i8*, i8** %p, align 8, !dbg !926
  %79 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !927
  %call119 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %79), !dbg !928
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive118, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.14, i32 0, i32 0), i8* %78, i8* %call119), !dbg !929
  store i32 -20, i32* %ret, align 4, !dbg !930
  br label %if.end120, !dbg !931

if.end120:                                        ; preds = %if.end117, %if.end107
  %80 = load i64, i64* %copy_length, align 8, !dbg !932
  %cmp121 = icmp ugt i64 %80, 0, !dbg !934
  br i1 %cmp121, label %if.then123, label %if.end131, !dbg !935

if.then123:                                       ; preds = %if.end120
  %81 = load i8*, i8** %p, align 8, !dbg !936
  %call124 = call i64 @strlen(i8* %81) #8, !dbg !939
  %cmp125 = icmp ugt i64 %call124, 32, !dbg !940
  br i1 %cmp125, label %if.then127, label %if.end129, !dbg !941

if.then127:                                       ; preds = %if.then123
  %82 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !942
  %archive128 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %82, i32 0, i32 0, !dbg !944
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive128, i32 -1, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.15, i32 0, i32 0)), !dbg !945
  store i32 -25, i32* %ret, align 4, !dbg !946
  store i64 32, i64* %copy_length, align 8, !dbg !947
  br label %if.end129, !dbg !948

if.end129:                                        ; preds = %if.then127, %if.then123
  %83 = load i8*, i8** %h.addr, align 8, !dbg !949
  %add.ptr130 = getelementptr inbounds i8, i8* %83, i64 297, !dbg !950
  %84 = load i8*, i8** %p, align 8, !dbg !951
  %85 = load i64, i64* %copy_length, align 8, !dbg !952
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr130, i8* %84, i64 %85, i32 1, i1 false), !dbg !953
  br label %if.end131, !dbg !954

if.end131:                                        ; preds = %if.end129, %if.end120
  %86 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !955
  %call132 = call i32 @archive_entry_mode(%struct.archive_entry* %86), !dbg !957
  %and = and i32 %call132, 4095, !dbg !958
  %conv133 = zext i32 %and to i64, !dbg !957
  %87 = load i8*, i8** %h.addr, align 8, !dbg !959
  %add.ptr134 = getelementptr inbounds i8, i8* %87, i64 100, !dbg !960
  %88 = load i32, i32* %strict.addr, align 4, !dbg !961
  %call135 = call i32 @format_number(i64 %conv133, i8* %add.ptr134, i32 6, i32 8, i32 %88), !dbg !962
  %tobool136 = icmp ne i32 %call135, 0, !dbg !964
  br i1 %tobool136, label %if.then137, label %if.end139, !dbg !965

if.then137:                                       ; preds = %if.end131
  %89 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !966
  %archive138 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %89, i32 0, i32 0, !dbg !968
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive138, i32 34, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.16, i32 0, i32 0)), !dbg !969
  store i32 -25, i32* %ret, align 4, !dbg !970
  br label %if.end139, !dbg !971

if.end139:                                        ; preds = %if.then137, %if.end131
  %90 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !972
  %call140 = call i64 @archive_entry_uid(%struct.archive_entry* %90), !dbg !974
  %91 = load i8*, i8** %h.addr, align 8, !dbg !975
  %add.ptr141 = getelementptr inbounds i8, i8* %91, i64 108, !dbg !976
  %92 = load i32, i32* %strict.addr, align 4, !dbg !977
  %call142 = call i32 @format_number(i64 %call140, i8* %add.ptr141, i32 6, i32 8, i32 %92), !dbg !978
  %tobool143 = icmp ne i32 %call142, 0, !dbg !980
  br i1 %tobool143, label %if.then144, label %if.end146, !dbg !981

if.then144:                                       ; preds = %if.end139
  %93 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !982
  %archive145 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %93, i32 0, i32 0, !dbg !984
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive145, i32 34, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.17, i32 0, i32 0)), !dbg !985
  store i32 -25, i32* %ret, align 4, !dbg !986
  br label %if.end146, !dbg !987

if.end146:                                        ; preds = %if.then144, %if.end139
  %94 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !988
  %call147 = call i64 @archive_entry_gid(%struct.archive_entry* %94), !dbg !990
  %95 = load i8*, i8** %h.addr, align 8, !dbg !991
  %add.ptr148 = getelementptr inbounds i8, i8* %95, i64 116, !dbg !992
  %96 = load i32, i32* %strict.addr, align 4, !dbg !993
  %call149 = call i32 @format_number(i64 %call147, i8* %add.ptr148, i32 6, i32 8, i32 %96), !dbg !994
  %tobool150 = icmp ne i32 %call149, 0, !dbg !996
  br i1 %tobool150, label %if.then151, label %if.end153, !dbg !997

if.then151:                                       ; preds = %if.end146
  %97 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !998
  %archive152 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %97, i32 0, i32 0, !dbg !1000
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive152, i32 34, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.18, i32 0, i32 0)), !dbg !1001
  store i32 -25, i32* %ret, align 4, !dbg !1002
  br label %if.end153, !dbg !1003

if.end153:                                        ; preds = %if.then151, %if.end146
  %98 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1004
  %call154 = call i64 @archive_entry_size(%struct.archive_entry* %98), !dbg !1006
  %99 = load i8*, i8** %h.addr, align 8, !dbg !1007
  %add.ptr155 = getelementptr inbounds i8, i8* %99, i64 124, !dbg !1008
  %100 = load i32, i32* %strict.addr, align 4, !dbg !1009
  %call156 = call i32 @format_number(i64 %call154, i8* %add.ptr155, i32 11, i32 12, i32 %100), !dbg !1010
  %tobool157 = icmp ne i32 %call156, 0, !dbg !1012
  br i1 %tobool157, label %if.then158, label %if.end160, !dbg !1013

if.then158:                                       ; preds = %if.end153
  %101 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1014
  %archive159 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %101, i32 0, i32 0, !dbg !1016
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive159, i32 34, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.19, i32 0, i32 0)), !dbg !1017
  store i32 -25, i32* %ret, align 4, !dbg !1018
  br label %if.end160, !dbg !1019

if.end160:                                        ; preds = %if.then158, %if.end153
  %102 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1020
  %call161 = call i64 @archive_entry_mtime(%struct.archive_entry* %102), !dbg !1022
  %103 = load i8*, i8** %h.addr, align 8, !dbg !1023
  %add.ptr162 = getelementptr inbounds i8, i8* %103, i64 136, !dbg !1024
  %104 = load i32, i32* %strict.addr, align 4, !dbg !1025
  %call163 = call i32 @format_number(i64 %call161, i8* %add.ptr162, i32 11, i32 11, i32 %104), !dbg !1026
  %tobool164 = icmp ne i32 %call163, 0, !dbg !1028
  br i1 %tobool164, label %if.then165, label %if.end167, !dbg !1029

if.then165:                                       ; preds = %if.end160
  %105 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1030
  %archive166 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %105, i32 0, i32 0, !dbg !1032
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive166, i32 34, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.20, i32 0, i32 0)), !dbg !1033
  store i32 -25, i32* %ret, align 4, !dbg !1034
  br label %if.end167, !dbg !1035

if.end167:                                        ; preds = %if.then165, %if.end160
  %106 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1036
  %call168 = call i32 @archive_entry_filetype(%struct.archive_entry* %106), !dbg !1038
  %cmp169 = icmp eq i32 %call168, 24576, !dbg !1039
  br i1 %cmp169, label %if.then174, label %lor.lhs.false, !dbg !1040

lor.lhs.false:                                    ; preds = %if.end167
  %107 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1041
  %call171 = call i32 @archive_entry_filetype(%struct.archive_entry* %107), !dbg !1043
  %cmp172 = icmp eq i32 %call171, 8192, !dbg !1044
  br i1 %cmp172, label %if.then174, label %if.end189, !dbg !1045

if.then174:                                       ; preds = %lor.lhs.false, %if.end167
  %108 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1047
  %call175 = call i64 @archive_entry_rdevmajor(%struct.archive_entry* %108), !dbg !1050
  %109 = load i8*, i8** %h.addr, align 8, !dbg !1051
  %add.ptr176 = getelementptr inbounds i8, i8* %109, i64 329, !dbg !1052
  %110 = load i32, i32* %strict.addr, align 4, !dbg !1053
  %call177 = call i32 @format_number(i64 %call175, i8* %add.ptr176, i32 6, i32 8, i32 %110), !dbg !1054
  %tobool178 = icmp ne i32 %call177, 0, !dbg !1056
  br i1 %tobool178, label %if.then179, label %if.end181, !dbg !1057

if.then179:                                       ; preds = %if.then174
  %111 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1058
  %archive180 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %111, i32 0, i32 0, !dbg !1060
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive180, i32 34, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.21, i32 0, i32 0)), !dbg !1061
  store i32 -25, i32* %ret, align 4, !dbg !1062
  br label %if.end181, !dbg !1063

if.end181:                                        ; preds = %if.then179, %if.then174
  %112 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1064
  %call182 = call i64 @archive_entry_rdevminor(%struct.archive_entry* %112), !dbg !1066
  %113 = load i8*, i8** %h.addr, align 8, !dbg !1067
  %add.ptr183 = getelementptr inbounds i8, i8* %113, i64 337, !dbg !1068
  %114 = load i32, i32* %strict.addr, align 4, !dbg !1069
  %call184 = call i32 @format_number(i64 %call182, i8* %add.ptr183, i32 6, i32 8, i32 %114), !dbg !1070
  %tobool185 = icmp ne i32 %call184, 0, !dbg !1072
  br i1 %tobool185, label %if.then186, label %if.end188, !dbg !1073

if.then186:                                       ; preds = %if.end181
  %115 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1074
  %archive187 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %115, i32 0, i32 0, !dbg !1076
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive187, i32 34, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.22, i32 0, i32 0)), !dbg !1077
  store i32 -25, i32* %ret, align 4, !dbg !1078
  br label %if.end188, !dbg !1079

if.end188:                                        ; preds = %if.then186, %if.end181
  br label %if.end189, !dbg !1080

if.end189:                                        ; preds = %if.end188, %lor.lhs.false
  %116 = load i32, i32* %tartype.addr, align 4, !dbg !1081
  %cmp190 = icmp sge i32 %116, 0, !dbg !1083
  br i1 %cmp190, label %if.then192, label %if.else195, !dbg !1084

if.then192:                                       ; preds = %if.end189
  %117 = load i32, i32* %tartype.addr, align 4, !dbg !1085
  %conv193 = trunc i32 %117 to i8, !dbg !1085
  %118 = load i8*, i8** %h.addr, align 8, !dbg !1087
  %arrayidx194 = getelementptr inbounds i8, i8* %118, i64 156, !dbg !1087
  store i8 %conv193, i8* %arrayidx194, align 1, !dbg !1088
  br label %if.end220, !dbg !1089

if.else195:                                       ; preds = %if.end189
  %119 = load i32, i32* %mytartype, align 4, !dbg !1090
  %cmp196 = icmp sge i32 %119, 0, !dbg !1093
  br i1 %cmp196, label %if.then198, label %if.else201, !dbg !1090

if.then198:                                       ; preds = %if.else195
  %120 = load i32, i32* %mytartype, align 4, !dbg !1094
  %conv199 = trunc i32 %120 to i8, !dbg !1094
  %121 = load i8*, i8** %h.addr, align 8, !dbg !1096
  %arrayidx200 = getelementptr inbounds i8, i8* %121, i64 156, !dbg !1096
  store i8 %conv199, i8* %arrayidx200, align 1, !dbg !1097
  br label %if.end219, !dbg !1098

if.else201:                                       ; preds = %if.else195
  %122 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1099
  %call202 = call i32 @archive_entry_filetype(%struct.archive_entry* %122), !dbg !1101
  switch i32 %call202, label %sw.default [
    i32 32768, label %sw.bb
    i32 40960, label %sw.bb204
    i32 8192, label %sw.bb206
    i32 24576, label %sw.bb208
    i32 16384, label %sw.bb210
    i32 4096, label %sw.bb212
    i32 49152, label %sw.bb214
  ], !dbg !1102

sw.bb:                                            ; preds = %if.else201
  %123 = load i8*, i8** %h.addr, align 8, !dbg !1103
  %arrayidx203 = getelementptr inbounds i8, i8* %123, i64 156, !dbg !1103
  store i8 48, i8* %arrayidx203, align 1, !dbg !1105
  br label %sw.epilog, !dbg !1106

sw.bb204:                                         ; preds = %if.else201
  %124 = load i8*, i8** %h.addr, align 8, !dbg !1107
  %arrayidx205 = getelementptr inbounds i8, i8* %124, i64 156, !dbg !1107
  store i8 50, i8* %arrayidx205, align 1, !dbg !1108
  br label %sw.epilog, !dbg !1109

sw.bb206:                                         ; preds = %if.else201
  %125 = load i8*, i8** %h.addr, align 8, !dbg !1110
  %arrayidx207 = getelementptr inbounds i8, i8* %125, i64 156, !dbg !1110
  store i8 51, i8* %arrayidx207, align 1, !dbg !1111
  br label %sw.epilog, !dbg !1112

sw.bb208:                                         ; preds = %if.else201
  %126 = load i8*, i8** %h.addr, align 8, !dbg !1113
  %arrayidx209 = getelementptr inbounds i8, i8* %126, i64 156, !dbg !1113
  store i8 52, i8* %arrayidx209, align 1, !dbg !1114
  br label %sw.epilog, !dbg !1115

sw.bb210:                                         ; preds = %if.else201
  %127 = load i8*, i8** %h.addr, align 8, !dbg !1116
  %arrayidx211 = getelementptr inbounds i8, i8* %127, i64 156, !dbg !1116
  store i8 53, i8* %arrayidx211, align 1, !dbg !1117
  br label %sw.epilog, !dbg !1118

sw.bb212:                                         ; preds = %if.else201
  %128 = load i8*, i8** %h.addr, align 8, !dbg !1119
  %arrayidx213 = getelementptr inbounds i8, i8* %128, i64 156, !dbg !1119
  store i8 54, i8* %arrayidx213, align 1, !dbg !1120
  br label %sw.epilog, !dbg !1121

sw.bb214:                                         ; preds = %if.else201
  %129 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1122
  %archive215 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %129, i32 0, i32 0, !dbg !1123
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive215, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.23, i32 0, i32 0)), !dbg !1124
  store i32 -25, i32* %retval, align 4, !dbg !1125
  br label %return, !dbg !1125

sw.default:                                       ; preds = %if.else201
  %130 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1126
  %archive216 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %130, i32 0, i32 0, !dbg !1127
  %131 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1128
  %call217 = call i32 @archive_entry_mode(%struct.archive_entry* %131), !dbg !1129
  %conv218 = zext i32 %call217 to i64, !dbg !1130
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive216, i32 84, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.24, i32 0, i32 0), i64 %conv218), !dbg !1131
  store i32 -25, i32* %ret, align 4, !dbg !1132
  br label %sw.epilog, !dbg !1133

sw.epilog:                                        ; preds = %sw.default, %sw.bb212, %sw.bb210, %sw.bb208, %sw.bb206, %sw.bb204, %sw.bb
  br label %if.end219

if.end219:                                        ; preds = %sw.epilog, %if.then198
  br label %if.end220

if.end220:                                        ; preds = %if.end219, %if.then192
  store i32 0, i32* %checksum, align 4, !dbg !1134
  store i32 0, i32* %i, align 4, !dbg !1135
  br label %for.cond, !dbg !1137

for.cond:                                         ; preds = %for.inc, %if.end220
  %132 = load i32, i32* %i, align 4, !dbg !1138
  %cmp221 = icmp slt i32 %132, 512, !dbg !1141
  br i1 %cmp221, label %for.body, label %for.end, !dbg !1142

for.body:                                         ; preds = %for.cond
  %133 = load i32, i32* %i, align 4, !dbg !1143
  %idxprom = sext i32 %133 to i64, !dbg !1144
  %134 = load i8*, i8** %h.addr, align 8, !dbg !1144
  %arrayidx223 = getelementptr inbounds i8, i8* %134, i64 %idxprom, !dbg !1144
  %135 = load i8, i8* %arrayidx223, align 1, !dbg !1144
  %conv224 = sext i8 %135 to i32, !dbg !1145
  %and225 = and i32 255, %conv224, !dbg !1146
  %136 = load i32, i32* %checksum, align 4, !dbg !1147
  %add = add i32 %136, %and225, !dbg !1147
  store i32 %add, i32* %checksum, align 4, !dbg !1147
  br label %for.inc, !dbg !1148

for.inc:                                          ; preds = %for.body
  %137 = load i32, i32* %i, align 4, !dbg !1149
  %inc = add nsw i32 %137, 1, !dbg !1149
  store i32 %inc, i32* %i, align 4, !dbg !1149
  br label %for.cond, !dbg !1151

for.end:                                          ; preds = %for.cond
  %138 = load i8*, i8** %h.addr, align 8, !dbg !1152
  %arrayidx226 = getelementptr inbounds i8, i8* %138, i64 154, !dbg !1152
  store i8 0, i8* %arrayidx226, align 1, !dbg !1153
  %139 = load i32, i32* %checksum, align 4, !dbg !1154
  %conv227 = zext i32 %139 to i64, !dbg !1154
  %140 = load i8*, i8** %h.addr, align 8, !dbg !1155
  %add.ptr228 = getelementptr inbounds i8, i8* %140, i64 148, !dbg !1156
  %call229 = call i32 @format_octal(i64 %conv227, i8* %add.ptr228, i32 6), !dbg !1157
  %141 = load i32, i32* %ret, align 4, !dbg !1158
  store i32 %141, i32* %retval, align 4, !dbg !1159
  br label %return, !dbg !1159

return:                                           ; preds = %for.end, %sw.bb214, %if.then115, %if.then92, %if.then68, %if.then51, %if.then4
  %142 = load i32, i32* %retval, align 4, !dbg !1160
  ret i32 %142, !dbg !1160
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #6

declare i32 @_archive_entry_hardlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i32 @_archive_entry_symlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i32 @_archive_entry_uname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i32 @_archive_entry_gname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #6

; Function Attrs: nounwind uwtable
define internal i32 @format_number(i64 %v, i8* %p, i32 %s, i32 %maxsize, i32 %strict) #0 !dbg !211 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %maxsize.addr = alloca i32, align 4
  %strict.addr = alloca i32, align 4
  %limit = alloca i64, align 8
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1161, metadata !231), !dbg !1162
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1163, metadata !231), !dbg !1164
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1165, metadata !231), !dbg !1166
  store i32 %maxsize, i32* %maxsize.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %maxsize.addr, metadata !1167, metadata !231), !dbg !1168
  store i32 %strict, i32* %strict.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %strict.addr, metadata !1169, metadata !231), !dbg !1170
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !1171, metadata !231), !dbg !1172
  %0 = load i32, i32* %s.addr, align 4, !dbg !1173
  %mul = mul nsw i32 %0, 3, !dbg !1174
  %sh_prom = zext i32 %mul to i64, !dbg !1175
  %shl = shl i64 1, %sh_prom, !dbg !1175
  store i64 %shl, i64* %limit, align 8, !dbg !1176
  %1 = load i32, i32* %strict.addr, align 4, !dbg !1177
  %tobool = icmp ne i32 %1, 0, !dbg !1177
  br i1 %tobool, label %if.then, label %if.end, !dbg !1179

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %v.addr, align 8, !dbg !1180
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1181
  %4 = load i32, i32* %s.addr, align 4, !dbg !1182
  %call = call i32 @format_octal(i64 %2, i8* %3, i32 %4), !dbg !1183
  store i32 %call, i32* %retval, align 4, !dbg !1184
  br label %return, !dbg !1184

if.end:                                           ; preds = %entry
  %5 = load i64, i64* %v.addr, align 8, !dbg !1185
  %cmp = icmp sge i64 %5, 0, !dbg !1187
  br i1 %cmp, label %if.then1, label %if.end8, !dbg !1188

if.then1:                                         ; preds = %if.end
  br label %while.cond, !dbg !1189

while.cond:                                       ; preds = %if.end6, %if.then1
  %6 = load i32, i32* %s.addr, align 4, !dbg !1191
  %7 = load i32, i32* %maxsize.addr, align 4, !dbg !1193
  %cmp2 = icmp sle i32 %6, %7, !dbg !1194
  br i1 %cmp2, label %while.body, label %while.end, !dbg !1195

while.body:                                       ; preds = %while.cond
  %8 = load i64, i64* %v.addr, align 8, !dbg !1196
  %9 = load i64, i64* %limit, align 8, !dbg !1199
  %cmp3 = icmp slt i64 %8, %9, !dbg !1200
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !1201

if.then4:                                         ; preds = %while.body
  %10 = load i64, i64* %v.addr, align 8, !dbg !1202
  %11 = load i8*, i8** %p.addr, align 8, !dbg !1203
  %12 = load i32, i32* %s.addr, align 4, !dbg !1204
  %call5 = call i32 @format_octal(i64 %10, i8* %11, i32 %12), !dbg !1205
  store i32 %call5, i32* %retval, align 4, !dbg !1206
  br label %return, !dbg !1206

if.end6:                                          ; preds = %while.body
  %13 = load i32, i32* %s.addr, align 4, !dbg !1207
  %inc = add nsw i32 %13, 1, !dbg !1207
  store i32 %inc, i32* %s.addr, align 4, !dbg !1207
  %14 = load i64, i64* %limit, align 8, !dbg !1208
  %shl7 = shl i64 %14, 3, !dbg !1208
  store i64 %shl7, i64* %limit, align 8, !dbg !1208
  br label %while.cond, !dbg !1209

while.end:                                        ; preds = %while.cond
  br label %if.end8, !dbg !1211

if.end8:                                          ; preds = %while.end, %if.end
  %15 = load i64, i64* %v.addr, align 8, !dbg !1212
  %16 = load i8*, i8** %p.addr, align 8, !dbg !1213
  %17 = load i32, i32* %maxsize.addr, align 4, !dbg !1214
  %call9 = call i32 @format_256(i64 %15, i8* %16, i32 %17), !dbg !1215
  store i32 %call9, i32* %retval, align 4, !dbg !1216
  br label %return, !dbg !1216

return:                                           ; preds = %if.end8, %if.then4, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !1217
  ret i32 %18, !dbg !1217
}

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevmajor(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevminor(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @format_octal(i64 %v, i8* %p, i32 %s) #0 !dbg !217 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %len = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1218, metadata !231), !dbg !1219
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1220, metadata !231), !dbg !1221
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1222, metadata !231), !dbg !1223
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1224, metadata !231), !dbg !1225
  %0 = load i32, i32* %s.addr, align 4, !dbg !1226
  store i32 %0, i32* %len, align 4, !dbg !1227
  %1 = load i64, i64* %v.addr, align 8, !dbg !1228
  %cmp = icmp slt i64 %1, 0, !dbg !1230
  br i1 %cmp, label %if.then, label %if.end, !dbg !1231

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !1232

while.cond:                                       ; preds = %while.body, %if.then
  %2 = load i32, i32* %len, align 4, !dbg !1234
  %dec = add nsw i32 %2, -1, !dbg !1234
  store i32 %dec, i32* %len, align 4, !dbg !1234
  %cmp1 = icmp sgt i32 %2, 0, !dbg !1236
  br i1 %cmp1, label %while.body, label %while.end, !dbg !1237

while.body:                                       ; preds = %while.cond
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1238
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !1238
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1238
  store i8 48, i8* %3, align 1, !dbg !1239
  br label %while.cond, !dbg !1240

while.end:                                        ; preds = %while.cond
  store i32 -1, i32* %retval, align 4, !dbg !1242
  br label %return, !dbg !1242

if.end:                                           ; preds = %entry
  %4 = load i32, i32* %s.addr, align 4, !dbg !1243
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1244
  %idx.ext = sext i32 %4 to i64, !dbg !1244
  %add.ptr = getelementptr inbounds i8, i8* %5, i64 %idx.ext, !dbg !1244
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1244
  br label %while.cond2, !dbg !1245

while.cond2:                                      ; preds = %while.body5, %if.end
  %6 = load i32, i32* %s.addr, align 4, !dbg !1246
  %dec3 = add nsw i32 %6, -1, !dbg !1246
  store i32 %dec3, i32* %s.addr, align 4, !dbg !1246
  %cmp4 = icmp sgt i32 %6, 0, !dbg !1248
  br i1 %cmp4, label %while.body5, label %while.end7, !dbg !1249

while.body5:                                      ; preds = %while.cond2
  %7 = load i64, i64* %v.addr, align 8, !dbg !1250
  %and = and i64 %7, 7, !dbg !1252
  %add = add nsw i64 48, %and, !dbg !1253
  %conv = trunc i64 %add to i8, !dbg !1254
  %8 = load i8*, i8** %p.addr, align 8, !dbg !1255
  %incdec.ptr6 = getelementptr inbounds i8, i8* %8, i32 -1, !dbg !1255
  store i8* %incdec.ptr6, i8** %p.addr, align 8, !dbg !1255
  store i8 %conv, i8* %incdec.ptr6, align 1, !dbg !1256
  %9 = load i64, i64* %v.addr, align 8, !dbg !1257
  %shr = ashr i64 %9, 3, !dbg !1257
  store i64 %shr, i64* %v.addr, align 8, !dbg !1257
  br label %while.cond2, !dbg !1258

while.end7:                                       ; preds = %while.cond2
  %10 = load i64, i64* %v.addr, align 8, !dbg !1260
  %cmp8 = icmp eq i64 %10, 0, !dbg !1262
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !1263

if.then10:                                        ; preds = %while.end7
  store i32 0, i32* %retval, align 4, !dbg !1264
  br label %return, !dbg !1264

if.end11:                                         ; preds = %while.end7
  br label %while.cond12, !dbg !1265

while.cond12:                                     ; preds = %while.body16, %if.end11
  %11 = load i32, i32* %len, align 4, !dbg !1266
  %dec13 = add nsw i32 %11, -1, !dbg !1266
  store i32 %dec13, i32* %len, align 4, !dbg !1266
  %cmp14 = icmp sgt i32 %11, 0, !dbg !1267
  br i1 %cmp14, label %while.body16, label %while.end18, !dbg !1268

while.body16:                                     ; preds = %while.cond12
  %12 = load i8*, i8** %p.addr, align 8, !dbg !1269
  %incdec.ptr17 = getelementptr inbounds i8, i8* %12, i32 1, !dbg !1269
  store i8* %incdec.ptr17, i8** %p.addr, align 8, !dbg !1269
  store i8 55, i8* %12, align 1, !dbg !1270
  br label %while.cond12, !dbg !1271

while.end18:                                      ; preds = %while.cond12
  store i32 -1, i32* %retval, align 4, !dbg !1272
  br label %return, !dbg !1272

return:                                           ; preds = %while.end18, %if.then10, %while.end
  %13 = load i32, i32* %retval, align 4, !dbg !1273
  ret i32 %13, !dbg !1273
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #6

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #2

declare %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #2

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_free(%struct.archive_entry*) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @format_256(i64 %v, i8* %p, i32 %s) #0 !dbg !214 {
entry:
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1274, metadata !231), !dbg !1275
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1276, metadata !231), !dbg !1277
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1278, metadata !231), !dbg !1279
  %0 = load i32, i32* %s.addr, align 4, !dbg !1280
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1281
  %idx.ext = sext i32 %0 to i64, !dbg !1281
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !1281
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1281
  br label %while.cond, !dbg !1282

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i32, i32* %s.addr, align 4, !dbg !1283
  %dec = add nsw i32 %2, -1, !dbg !1283
  store i32 %dec, i32* %s.addr, align 4, !dbg !1283
  %cmp = icmp sgt i32 %2, 0, !dbg !1285
  br i1 %cmp, label %while.body, label %while.end, !dbg !1286

while.body:                                       ; preds = %while.cond
  %3 = load i64, i64* %v.addr, align 8, !dbg !1287
  %and = and i64 %3, 255, !dbg !1289
  %conv = trunc i64 %and to i8, !dbg !1290
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1291
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 -1, !dbg !1291
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1291
  store i8 %conv, i8* %incdec.ptr, align 1, !dbg !1292
  %5 = load i64, i64* %v.addr, align 8, !dbg !1293
  %shr = ashr i64 %5, 8, !dbg !1293
  store i64 %shr, i64* %v.addr, align 8, !dbg !1293
  br label %while.cond, !dbg !1294

while.end:                                        ; preds = %while.cond
  %6 = load i8*, i8** %p.addr, align 8, !dbg !1296
  %7 = load i8, i8* %6, align 1, !dbg !1297
  %conv1 = sext i8 %7 to i32, !dbg !1297
  %or = or i32 %conv1, 128, !dbg !1297
  %conv2 = trunc i32 %or to i8, !dbg !1297
  store i8 %conv2, i8* %6, align 1, !dbg !1297
  ret i32 0, !dbg !1298
}

declare i32 @__archive_write_nulls(%struct.archive_write*, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!227, !228}
!llvm.ident = !{!229}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !204, globals: !222)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_ustar.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !124, !192, !201, !47, !13, !52, !82, !45}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !111, !112, !113, !114, !118, !119, !125, !131, !134, !135, !136, !137, !163, !164, !165, !166, !170, !174, !175, !179, !183, !184, !185, !186, !191}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !105, !106, !107, !108, !109, !110}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !104, line: 36, flags: DIFlagFwdDecl)
!104 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_locale.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !115, size: 64, align: 64, offset: 1472)
!115 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !116, size: 64, align: 64)
!116 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !117)
!117 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !120, size: 64, align: 64, offset: 1600)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !122)
!122 = !DISubroutineType(types: !123)
!123 = !{!23, !24, !124}
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !126, size: 64, align: 64, offset: 1664)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !128)
!128 = !DISubroutineType(types: !129)
!129 = !{!130, !24, !124, !43, !45}
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !132, size: 64, align: 64, offset: 1728)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !122)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !124, size: 64, align: 64, offset: 1792)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !138, size: 64, align: 64, offset: 1920)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !140)
!140 = !{!141, !142, !143, !144, !148, !152, !156, !157, !158, !159, !160, !161, !162}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !139, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !139, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !139, file: !6, line: 46, baseType: !138, size: 64, align: 64, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !139, file: !6, line: 47, baseType: !145, size: 64, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DISubroutineType(types: !147)
!147 = !{!23, !138, !80, !80}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !139, file: !6, line: 49, baseType: !149, size: 64, align: 64, offset: 256)
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !150, size: 64, align: 64)
!150 = !DISubroutineType(types: !151)
!151 = !{!23, !138}
!152 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !139, file: !6, line: 50, baseType: !153, size: 64, align: 64, offset: 320)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DISubroutineType(types: !155)
!155 = !{!23, !138, !43, !45}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !139, file: !6, line: 51, baseType: !149, size: 64, align: 64, offset: 384)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !139, file: !6, line: 52, baseType: !149, size: 64, align: 64, offset: 448)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !139, file: !6, line: 53, baseType: !124, size: 64, align: 64, offset: 512)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !139, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !139, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !139, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !139, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !138, size: 64, align: 64, offset: 1984)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !124, size: 64, align: 64, offset: 2048)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !167, size: 64, align: 64, offset: 2176)
!167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!168 = !DISubroutineType(types: !169)
!169 = !{!23, !4}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !171, size: 64, align: 64, offset: 2240)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DISubroutineType(types: !173)
!173 = !{!23, !4, !80, !80}
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !167, size: 64, align: 64, offset: 2304)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !176, size: 64, align: 64, offset: 2368)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DISubroutineType(types: !178)
!178 = !{!23, !4, !30}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !180, size: 64, align: 64, offset: 2432)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DISubroutineType(types: !182)
!182 = !{!38, !4, !43, !45}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !167, size: 64, align: 64, offset: 2496)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !167, size: 64, align: 64, offset: 2560)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !187, size: 64, align: 64, offset: 2688)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !189)
!189 = !DISubroutineType(types: !190)
!190 = !{!80, !24, !124}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !124, size: 64, align: 64, offset: 2752)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "ustar", file: !1, line: 48, size: 320, align: 64, elements: !194)
!194 = !{!195, !197, !198, !199, !200}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !193, file: !1, line: 49, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !193, file: !1, line: 50, baseType: !196, size: 64, align: 64, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !193, file: !1, line: 52, baseType: !102, size: 64, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !193, file: !1, line: 53, baseType: !102, size: 64, align: 64, offset: 192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !193, file: !1, line: 54, baseType: !23, size: 32, align: 32, offset: 256)
!201 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !202, line: 70, baseType: !203)
!202 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!204 = !{!205, !206, !209, !210, !211, !214, !217, !218, !219, !220, !221}
!205 = distinct !DISubprogram(name: "archive_write_set_format_ustar", scope: !1, file: !1, line: 167, type: !21, isLocal: false, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!206 = distinct !DISubprogram(name: "__archive_write_format_header_ustar", scope: !1, file: !1, line: 386, type: !207, isLocal: false, isDefinition: true, scopeLine: 389, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!207 = !DISubroutineType(types: !208)
!208 = !{!23, !4, !95, !30, !23, !23, !102}
!209 = distinct !DISubprogram(name: "archive_write_ustar_options", scope: !1, file: !1, line: 207, type: !172, isLocal: true, isDefinition: true, scopeLine: 209, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!210 = distinct !DISubprogram(name: "archive_write_ustar_header", scope: !1, file: !1, line: 236, type: !177, isLocal: true, isDefinition: true, scopeLine: 237, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!211 = distinct !DISubprogram(name: "format_number", scope: !1, file: !1, line: 642, type: !212, isLocal: true, isDefinition: true, scopeLine: 643, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!212 = !DISubroutineType(types: !213)
!213 = !{!23, !52, !95, !23, !23, !23}
!214 = distinct !DISubprogram(name: "format_256", scope: !1, file: !1, line: 675, type: !215, isLocal: true, isDefinition: true, scopeLine: 676, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = !DISubroutineType(types: !216)
!216 = !{!23, !52, !95, !23}
!217 = distinct !DISubprogram(name: "format_octal", scope: !1, file: !1, line: 690, type: !215, isLocal: true, isDefinition: true, scopeLine: 691, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!218 = distinct !DISubprogram(name: "archive_write_ustar_close", scope: !1, file: !1, line: 720, type: !168, isLocal: true, isDefinition: true, scopeLine: 721, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!219 = distinct !DISubprogram(name: "archive_write_ustar_free", scope: !1, file: !1, line: 726, type: !168, isLocal: true, isDefinition: true, scopeLine: 727, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = distinct !DISubprogram(name: "archive_write_ustar_finish_entry", scope: !1, file: !1, line: 737, type: !168, isLocal: true, isDefinition: true, scopeLine: 738, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_write_ustar_data", scope: !1, file: !1, line: 750, type: !181, isLocal: true, isDefinition: true, scopeLine: 751, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = !{!223}
!223 = !DIGlobalVariable(name: "template_header", scope: !0, file: !1, line: 105, type: !224, isLocal: true, isDefinition: true, variable: [512 x i8]* @template_header)
!224 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 4096, align: 8, elements: !225)
!225 = !{!226}
!226 = !DISubrange(count: 512)
!227 = !{i32 2, !"Dwarf Version", i32 4}
!228 = !{i32 2, !"Debug Info Version", i32 3}
!229 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!230 = !DILocalVariable(name: "_a", arg: 1, scope: !205, file: !1, line: 167, type: !24)
!231 = !DIExpression()
!232 = !DILocation(line: 167, column: 48, scope: !205)
!233 = !DILocalVariable(name: "a", scope: !205, file: !1, line: 169, type: !4)
!234 = !DILocation(line: 169, column: 24, scope: !205)
!235 = !DILocation(line: 169, column: 52, scope: !205)
!236 = !DILocation(line: 169, column: 28, scope: !205)
!237 = !DILocalVariable(name: "ustar", scope: !205, file: !1, line: 170, type: !192)
!238 = !DILocation(line: 170, column: 16, scope: !205)
!239 = !DILocation(line: 172, column: 2, scope: !205)
!240 = !DILocalVariable(name: "magic_test", scope: !241, file: !1, line: 172, type: !23)
!241 = distinct !DILexicalBlock(scope: !205, file: !1, line: 172, column: 2)
!242 = !DILocation(line: 172, column: 2, scope: !241)
!243 = !DILocation(line: 172, column: 2, scope: !244)
!244 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 1)
!245 = !DILocation(line: 172, column: 2, scope: !246)
!246 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 2)
!247 = distinct !DILexicalBlock(scope: !241, file: !1, line: 172, column: 2)
!248 = !DILocation(line: 172, column: 2, scope: !249)
!249 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 3)
!250 = !DILocation(line: 176, column: 6, scope: !251)
!251 = distinct !DILexicalBlock(scope: !205, file: !1, line: 176, column: 6)
!252 = !DILocation(line: 176, column: 9, scope: !251)
!253 = !DILocation(line: 176, column: 21, scope: !251)
!254 = !DILocation(line: 176, column: 6, scope: !205)
!255 = !DILocation(line: 177, column: 4, scope: !251)
!256 = !DILocation(line: 177, column: 7, scope: !251)
!257 = !DILocation(line: 177, column: 20, scope: !251)
!258 = !DILocation(line: 177, column: 3, scope: !251)
!259 = !DILocation(line: 187, column: 26, scope: !205)
!260 = !DILocation(line: 187, column: 10, scope: !205)
!261 = !DILocation(line: 187, column: 8, scope: !205)
!262 = !DILocation(line: 188, column: 6, scope: !263)
!263 = distinct !DILexicalBlock(scope: !205, file: !1, line: 188, column: 6)
!264 = !DILocation(line: 188, column: 12, scope: !263)
!265 = !DILocation(line: 188, column: 6, scope: !205)
!266 = !DILocation(line: 189, column: 22, scope: !267)
!267 = distinct !DILexicalBlock(scope: !263, file: !1, line: 188, column: 21)
!268 = !DILocation(line: 189, column: 25, scope: !267)
!269 = !DILocation(line: 189, column: 3, scope: !267)
!270 = !DILocation(line: 191, column: 3, scope: !267)
!271 = !DILocation(line: 193, column: 19, scope: !205)
!272 = !DILocation(line: 193, column: 2, scope: !205)
!273 = !DILocation(line: 193, column: 5, scope: !205)
!274 = !DILocation(line: 193, column: 17, scope: !205)
!275 = !DILocation(line: 194, column: 2, scope: !205)
!276 = !DILocation(line: 194, column: 5, scope: !205)
!277 = !DILocation(line: 194, column: 17, scope: !205)
!278 = !DILocation(line: 195, column: 2, scope: !205)
!279 = !DILocation(line: 195, column: 5, scope: !205)
!280 = !DILocation(line: 195, column: 20, scope: !205)
!281 = !DILocation(line: 196, column: 2, scope: !205)
!282 = !DILocation(line: 196, column: 5, scope: !205)
!283 = !DILocation(line: 196, column: 25, scope: !205)
!284 = !DILocation(line: 197, column: 2, scope: !205)
!285 = !DILocation(line: 197, column: 5, scope: !205)
!286 = !DILocation(line: 197, column: 23, scope: !205)
!287 = !DILocation(line: 198, column: 2, scope: !205)
!288 = !DILocation(line: 198, column: 5, scope: !205)
!289 = !DILocation(line: 198, column: 18, scope: !205)
!290 = !DILocation(line: 199, column: 2, scope: !205)
!291 = !DILocation(line: 199, column: 5, scope: !205)
!292 = !DILocation(line: 199, column: 17, scope: !205)
!293 = !DILocation(line: 200, column: 2, scope: !205)
!294 = !DILocation(line: 200, column: 5, scope: !205)
!295 = !DILocation(line: 200, column: 25, scope: !205)
!296 = !DILocation(line: 201, column: 2, scope: !205)
!297 = !DILocation(line: 201, column: 5, scope: !205)
!298 = !DILocation(line: 201, column: 13, scope: !205)
!299 = !DILocation(line: 201, column: 28, scope: !205)
!300 = !DILocation(line: 202, column: 2, scope: !205)
!301 = !DILocation(line: 202, column: 5, scope: !205)
!302 = !DILocation(line: 202, column: 13, scope: !205)
!303 = !DILocation(line: 202, column: 33, scope: !205)
!304 = !DILocation(line: 203, column: 2, scope: !205)
!305 = !DILocation(line: 204, column: 1, scope: !205)
!306 = !DILocalVariable(name: "a", arg: 1, scope: !209, file: !1, line: 207, type: !4)
!307 = !DILocation(line: 207, column: 51, scope: !209)
!308 = !DILocalVariable(name: "key", arg: 2, scope: !209, file: !1, line: 207, type: !80)
!309 = !DILocation(line: 207, column: 66, scope: !209)
!310 = !DILocalVariable(name: "val", arg: 3, scope: !209, file: !1, line: 208, type: !80)
!311 = !DILocation(line: 208, column: 17, scope: !209)
!312 = !DILocalVariable(name: "ustar", scope: !209, file: !1, line: 210, type: !192)
!313 = !DILocation(line: 210, column: 16, scope: !209)
!314 = !DILocation(line: 210, column: 40, scope: !209)
!315 = !DILocation(line: 210, column: 43, scope: !209)
!316 = !DILocation(line: 210, column: 24, scope: !209)
!317 = !DILocalVariable(name: "ret", scope: !209, file: !1, line: 211, type: !23)
!318 = !DILocation(line: 211, column: 6, scope: !209)
!319 = !DILocation(line: 213, column: 13, scope: !320)
!320 = distinct !DILexicalBlock(scope: !209, file: !1, line: 213, column: 6)
!321 = !DILocation(line: 213, column: 6, scope: !320)
!322 = !DILocation(line: 213, column: 33, scope: !320)
!323 = !DILocation(line: 213, column: 6, scope: !209)
!324 = !DILocation(line: 214, column: 7, scope: !325)
!325 = distinct !DILexicalBlock(scope: !326, file: !1, line: 214, column: 7)
!326 = distinct !DILexicalBlock(scope: !320, file: !1, line: 213, column: 39)
!327 = !DILocation(line: 214, column: 11, scope: !325)
!328 = !DILocation(line: 214, column: 19, scope: !325)
!329 = !DILocation(line: 214, column: 22, scope: !330)
!330 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 1)
!331 = !DILocation(line: 214, column: 29, scope: !330)
!332 = !DILocation(line: 214, column: 7, scope: !330)
!333 = !DILocation(line: 215, column: 23, scope: !325)
!334 = !DILocation(line: 215, column: 26, scope: !325)
!335 = !DILocation(line: 217, column: 8, scope: !325)
!336 = !DILocation(line: 217, column: 11, scope: !325)
!337 = !DILocation(line: 215, column: 4, scope: !325)
!338 = !DILocation(line: 220, column: 9, scope: !339)
!339 = distinct !DILexicalBlock(scope: !325, file: !1, line: 218, column: 8)
!340 = !DILocation(line: 220, column: 12, scope: !339)
!341 = !DILocation(line: 220, column: 21, scope: !339)
!342 = !DILocation(line: 219, column: 23, scope: !339)
!343 = !DILocation(line: 219, column: 4, scope: !339)
!344 = !DILocation(line: 219, column: 11, scope: !339)
!345 = !DILocation(line: 219, column: 21, scope: !339)
!346 = !DILocation(line: 221, column: 8, scope: !347)
!347 = distinct !DILexicalBlock(scope: !339, file: !1, line: 221, column: 8)
!348 = !DILocation(line: 221, column: 15, scope: !347)
!349 = !DILocation(line: 221, column: 25, scope: !347)
!350 = !DILocation(line: 221, column: 8, scope: !339)
!351 = !DILocation(line: 222, column: 9, scope: !347)
!352 = !DILocation(line: 222, column: 5, scope: !347)
!353 = !DILocation(line: 224, column: 9, scope: !347)
!354 = !DILocation(line: 226, column: 11, scope: !326)
!355 = !DILocation(line: 226, column: 3, scope: !326)
!356 = !DILocation(line: 232, column: 2, scope: !209)
!357 = !DILocation(line: 233, column: 1, scope: !209)
!358 = !DILocalVariable(name: "a", arg: 1, scope: !210, file: !1, line: 236, type: !4)
!359 = !DILocation(line: 236, column: 50, scope: !210)
!360 = !DILocalVariable(name: "entry", arg: 2, scope: !210, file: !1, line: 236, type: !30)
!361 = !DILocation(line: 236, column: 75, scope: !210)
!362 = !DILocalVariable(name: "buff", scope: !210, file: !1, line: 238, type: !363)
!363 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 4096, align: 8, elements: !225)
!364 = !DILocation(line: 238, column: 7, scope: !210)
!365 = !DILocalVariable(name: "ret", scope: !210, file: !1, line: 239, type: !23)
!366 = !DILocation(line: 239, column: 6, scope: !210)
!367 = !DILocalVariable(name: "ret2", scope: !210, file: !1, line: 239, type: !23)
!368 = !DILocation(line: 239, column: 11, scope: !210)
!369 = !DILocalVariable(name: "ustar", scope: !210, file: !1, line: 240, type: !192)
!370 = !DILocation(line: 240, column: 16, scope: !210)
!371 = !DILocalVariable(name: "entry_main", scope: !210, file: !1, line: 241, type: !30)
!372 = !DILocation(line: 241, column: 24, scope: !210)
!373 = !DILocalVariable(name: "sconv", scope: !210, file: !1, line: 242, type: !102)
!374 = !DILocation(line: 242, column: 30, scope: !210)
!375 = !DILocation(line: 244, column: 26, scope: !210)
!376 = !DILocation(line: 244, column: 29, scope: !210)
!377 = !DILocation(line: 244, column: 10, scope: !210)
!378 = !DILocation(line: 244, column: 8, scope: !210)
!379 = !DILocation(line: 247, column: 6, scope: !380)
!380 = distinct !DILexicalBlock(scope: !210, file: !1, line: 247, column: 6)
!381 = !DILocation(line: 247, column: 13, scope: !380)
!382 = !DILocation(line: 247, column: 23, scope: !380)
!383 = !DILocation(line: 247, column: 6, scope: !210)
!384 = !DILocation(line: 248, column: 8, scope: !385)
!385 = distinct !DILexicalBlock(scope: !386, file: !1, line: 248, column: 7)
!386 = distinct !DILexicalBlock(scope: !380, file: !1, line: 247, column: 32)
!387 = !DILocation(line: 248, column: 15, scope: !385)
!388 = !DILocation(line: 248, column: 7, scope: !386)
!389 = !DILocation(line: 250, column: 54, scope: !390)
!390 = distinct !DILexicalBlock(scope: !385, file: !1, line: 248, column: 40)
!391 = !DILocation(line: 250, column: 57, scope: !390)
!392 = !DILocation(line: 250, column: 8, scope: !390)
!393 = !DILocation(line: 249, column: 4, scope: !390)
!394 = !DILocation(line: 249, column: 11, scope: !390)
!395 = !DILocation(line: 249, column: 25, scope: !390)
!396 = !DILocation(line: 251, column: 4, scope: !390)
!397 = !DILocation(line: 251, column: 11, scope: !390)
!398 = !DILocation(line: 251, column: 35, scope: !390)
!399 = !DILocation(line: 252, column: 3, scope: !390)
!400 = !DILocation(line: 253, column: 11, scope: !386)
!401 = !DILocation(line: 253, column: 18, scope: !386)
!402 = !DILocation(line: 253, column: 9, scope: !386)
!403 = !DILocation(line: 254, column: 2, scope: !386)
!404 = !DILocation(line: 255, column: 11, scope: !380)
!405 = !DILocation(line: 255, column: 18, scope: !380)
!406 = !DILocation(line: 255, column: 9, scope: !380)
!407 = !DILocation(line: 258, column: 29, scope: !408)
!408 = distinct !DILexicalBlock(scope: !210, file: !1, line: 258, column: 6)
!409 = !DILocation(line: 258, column: 6, scope: !408)
!410 = !DILocation(line: 258, column: 36, scope: !408)
!411 = !DILocation(line: 258, column: 6, scope: !210)
!412 = !DILocation(line: 259, column: 22, scope: !413)
!413 = distinct !DILexicalBlock(scope: !408, file: !1, line: 258, column: 45)
!414 = !DILocation(line: 259, column: 25, scope: !413)
!415 = !DILocation(line: 259, column: 3, scope: !413)
!416 = !DILocation(line: 261, column: 3, scope: !413)
!417 = !DILocation(line: 265, column: 29, scope: !418)
!418 = distinct !DILexicalBlock(scope: !210, file: !1, line: 265, column: 6)
!419 = !DILocation(line: 265, column: 6, scope: !418)
!420 = !DILocation(line: 265, column: 36, scope: !418)
!421 = !DILocation(line: 265, column: 44, scope: !418)
!422 = !DILocation(line: 266, column: 28, scope: !418)
!423 = !DILocation(line: 266, column: 6, scope: !418)
!424 = !DILocation(line: 266, column: 35, scope: !418)
!425 = !DILocation(line: 266, column: 43, scope: !418)
!426 = !DILocation(line: 267, column: 31, scope: !418)
!427 = !DILocation(line: 267, column: 8, scope: !418)
!428 = !DILocation(line: 267, column: 38, scope: !418)
!429 = !DILocation(line: 265, column: 6, scope: !430)
!430 = !DILexicalBlockFile(scope: !210, file: !1, discriminator: 1)
!431 = !DILocation(line: 268, column: 26, scope: !418)
!432 = !DILocation(line: 268, column: 3, scope: !418)
!433 = !DILocation(line: 270, column: 41, scope: !434)
!434 = distinct !DILexicalBlock(scope: !210, file: !1, line: 270, column: 6)
!435 = !DILocation(line: 270, column: 18, scope: !434)
!436 = !DILocation(line: 270, column: 15, scope: !434)
!437 = !DILocation(line: 270, column: 6, scope: !210)
!438 = !DILocalVariable(name: "p", scope: !439, file: !1, line: 271, type: !80)
!439 = distinct !DILexicalBlock(scope: !434, file: !1, line: 270, column: 49)
!440 = !DILocation(line: 271, column: 15, scope: !439)
!441 = !DILocalVariable(name: "path_length", scope: !439, file: !1, line: 272, type: !45)
!442 = !DILocation(line: 272, column: 10, scope: !439)
!443 = !DILocation(line: 303, column: 31, scope: !439)
!444 = !DILocation(line: 303, column: 8, scope: !439)
!445 = !DILocation(line: 303, column: 6, scope: !439)
!446 = !DILocation(line: 309, column: 7, scope: !447)
!447 = distinct !DILexicalBlock(scope: !439, file: !1, line: 309, column: 7)
!448 = !DILocation(line: 309, column: 9, scope: !447)
!449 = !DILocation(line: 309, column: 17, scope: !447)
!450 = !DILocation(line: 309, column: 20, scope: !451)
!451 = !DILexicalBlockFile(scope: !447, file: !1, discriminator: 1)
!452 = !DILocation(line: 309, column: 25, scope: !451)
!453 = !DILocation(line: 309, column: 33, scope: !451)
!454 = !DILocation(line: 309, column: 45, scope: !455)
!455 = !DILexicalBlockFile(scope: !447, file: !1, discriminator: 2)
!456 = !DILocation(line: 309, column: 38, scope: !455)
!457 = !DILocation(line: 309, column: 48, scope: !455)
!458 = !DILocation(line: 309, column: 36, scope: !455)
!459 = !DILocation(line: 309, column: 53, scope: !455)
!460 = !DILocation(line: 309, column: 7, scope: !455)
!461 = !DILocalVariable(name: "as", scope: !462, file: !1, line: 310, type: !91)
!462 = distinct !DILexicalBlock(scope: !447, file: !1, line: 309, column: 61)
!463 = !DILocation(line: 310, column: 26, scope: !462)
!464 = !DILocation(line: 312, column: 4, scope: !462)
!465 = !DILocation(line: 312, column: 4, scope: !466)
!466 = !DILexicalBlockFile(scope: !467, file: !1, discriminator: 1)
!467 = distinct !DILexicalBlock(scope: !462, file: !1, line: 312, column: 4)
!468 = !DILocation(line: 313, column: 25, scope: !462)
!469 = !DILocation(line: 313, column: 18, scope: !462)
!470 = !DILocation(line: 313, column: 16, scope: !462)
!471 = !DILocation(line: 315, column: 8, scope: !472)
!472 = distinct !DILexicalBlock(scope: !462, file: !1, line: 314, column: 8)
!473 = !DILocation(line: 315, column: 20, scope: !472)
!474 = !DILocation(line: 314, column: 8, scope: !472)
!475 = !DILocation(line: 315, column: 25, scope: !472)
!476 = !DILocation(line: 314, column: 8, scope: !462)
!477 = !DILocation(line: 316, column: 24, scope: !478)
!478 = distinct !DILexicalBlock(scope: !472, file: !1, line: 315, column: 34)
!479 = !DILocation(line: 316, column: 27, scope: !478)
!480 = !DILocation(line: 316, column: 5, scope: !478)
!481 = !DILocation(line: 318, column: 5, scope: !478)
!482 = !DILocation(line: 319, column: 5, scope: !478)
!483 = !DILocation(line: 330, column: 4, scope: !462)
!484 = !DILocation(line: 331, column: 4, scope: !462)
!485 = !DILocation(line: 332, column: 32, scope: !462)
!486 = !DILocation(line: 332, column: 42, scope: !462)
!487 = !DILocation(line: 332, column: 4, scope: !462)
!488 = !DILocation(line: 333, column: 4, scope: !462)
!489 = !DILocation(line: 334, column: 3, scope: !462)
!490 = !DILocation(line: 335, column: 2, scope: !439)
!491 = !DILocation(line: 351, column: 13, scope: !210)
!492 = !DILocation(line: 353, column: 44, scope: !210)
!493 = !DILocation(line: 353, column: 47, scope: !210)
!494 = !DILocation(line: 353, column: 53, scope: !210)
!495 = !DILocation(line: 353, column: 67, scope: !210)
!496 = !DILocation(line: 353, column: 8, scope: !210)
!497 = !DILocation(line: 353, column: 6, scope: !210)
!498 = !DILocation(line: 354, column: 6, scope: !499)
!499 = distinct !DILexicalBlock(scope: !210, file: !1, line: 354, column: 6)
!500 = !DILocation(line: 354, column: 10, scope: !499)
!501 = !DILocation(line: 354, column: 6, scope: !210)
!502 = !DILocation(line: 355, column: 7, scope: !503)
!503 = distinct !DILexicalBlock(scope: !504, file: !1, line: 355, column: 7)
!504 = distinct !DILexicalBlock(scope: !499, file: !1, line: 354, column: 26)
!505 = !DILocation(line: 355, column: 7, scope: !504)
!506 = !DILocation(line: 356, column: 23, scope: !503)
!507 = !DILocation(line: 356, column: 4, scope: !503)
!508 = !DILocation(line: 357, column: 11, scope: !504)
!509 = !DILocation(line: 357, column: 3, scope: !504)
!510 = !DILocation(line: 359, column: 32, scope: !210)
!511 = !DILocation(line: 359, column: 35, scope: !210)
!512 = !DILocation(line: 359, column: 9, scope: !210)
!513 = !DILocation(line: 359, column: 7, scope: !210)
!514 = !DILocation(line: 360, column: 6, scope: !515)
!515 = distinct !DILexicalBlock(scope: !210, file: !1, line: 360, column: 6)
!516 = !DILocation(line: 360, column: 11, scope: !515)
!517 = !DILocation(line: 360, column: 6, scope: !210)
!518 = !DILocation(line: 361, column: 7, scope: !519)
!519 = distinct !DILexicalBlock(scope: !520, file: !1, line: 361, column: 7)
!520 = distinct !DILexicalBlock(scope: !515, file: !1, line: 360, column: 27)
!521 = !DILocation(line: 361, column: 7, scope: !520)
!522 = !DILocation(line: 362, column: 23, scope: !519)
!523 = !DILocation(line: 362, column: 4, scope: !519)
!524 = !DILocation(line: 363, column: 11, scope: !520)
!525 = !DILocation(line: 363, column: 3, scope: !520)
!526 = !DILocation(line: 365, column: 6, scope: !527)
!527 = distinct !DILexicalBlock(scope: !210, file: !1, line: 365, column: 6)
!528 = !DILocation(line: 365, column: 13, scope: !527)
!529 = !DILocation(line: 365, column: 11, scope: !527)
!530 = !DILocation(line: 365, column: 6, scope: !210)
!531 = !DILocation(line: 366, column: 9, scope: !527)
!532 = !DILocation(line: 366, column: 7, scope: !527)
!533 = !DILocation(line: 366, column: 3, scope: !527)
!534 = !DILocation(line: 368, column: 52, scope: !210)
!535 = !DILocation(line: 368, column: 33, scope: !210)
!536 = !DILocation(line: 368, column: 2, scope: !210)
!537 = !DILocation(line: 368, column: 9, scope: !210)
!538 = !DILocation(line: 368, column: 31, scope: !210)
!539 = !DILocation(line: 369, column: 44, scope: !210)
!540 = !DILocation(line: 369, column: 51, scope: !210)
!541 = !DILocation(line: 369, column: 34, scope: !210)
!542 = !DILocation(line: 369, column: 31, scope: !210)
!543 = !DILocation(line: 369, column: 2, scope: !210)
!544 = !DILocation(line: 369, column: 9, scope: !210)
!545 = !DILocation(line: 369, column: 23, scope: !210)
!546 = !DILocation(line: 370, column: 6, scope: !547)
!547 = distinct !DILexicalBlock(scope: !210, file: !1, line: 370, column: 6)
!548 = !DILocation(line: 370, column: 6, scope: !210)
!549 = !DILocation(line: 371, column: 22, scope: !547)
!550 = !DILocation(line: 371, column: 3, scope: !547)
!551 = !DILocation(line: 372, column: 10, scope: !210)
!552 = !DILocation(line: 372, column: 2, scope: !210)
!553 = !DILocation(line: 373, column: 1, scope: !210)
!554 = !DILocalVariable(name: "a", arg: 1, scope: !221, file: !1, line: 750, type: !4)
!555 = !DILocation(line: 750, column: 48, scope: !221)
!556 = !DILocalVariable(name: "buff", arg: 2, scope: !221, file: !1, line: 750, type: !43)
!557 = !DILocation(line: 750, column: 63, scope: !221)
!558 = !DILocalVariable(name: "s", arg: 3, scope: !221, file: !1, line: 750, type: !45)
!559 = !DILocation(line: 750, column: 76, scope: !221)
!560 = !DILocalVariable(name: "ustar", scope: !221, file: !1, line: 752, type: !192)
!561 = !DILocation(line: 752, column: 16, scope: !221)
!562 = !DILocalVariable(name: "ret", scope: !221, file: !1, line: 753, type: !23)
!563 = !DILocation(line: 753, column: 6, scope: !221)
!564 = !DILocation(line: 755, column: 26, scope: !221)
!565 = !DILocation(line: 755, column: 29, scope: !221)
!566 = !DILocation(line: 755, column: 10, scope: !221)
!567 = !DILocation(line: 755, column: 8, scope: !221)
!568 = !DILocation(line: 756, column: 6, scope: !569)
!569 = distinct !DILexicalBlock(scope: !221, file: !1, line: 756, column: 6)
!570 = !DILocation(line: 756, column: 10, scope: !569)
!571 = !DILocation(line: 756, column: 17, scope: !569)
!572 = !DILocation(line: 756, column: 8, scope: !569)
!573 = !DILocation(line: 756, column: 6, scope: !221)
!574 = !DILocation(line: 757, column: 15, scope: !569)
!575 = !DILocation(line: 757, column: 22, scope: !569)
!576 = !DILocation(line: 757, column: 5, scope: !569)
!577 = !DILocation(line: 757, column: 3, scope: !569)
!578 = !DILocation(line: 758, column: 31, scope: !221)
!579 = !DILocation(line: 758, column: 34, scope: !221)
!580 = !DILocation(line: 758, column: 40, scope: !221)
!581 = !DILocation(line: 758, column: 8, scope: !221)
!582 = !DILocation(line: 758, column: 6, scope: !221)
!583 = !DILocation(line: 759, column: 34, scope: !221)
!584 = !DILocation(line: 759, column: 2, scope: !221)
!585 = !DILocation(line: 759, column: 9, scope: !221)
!586 = !DILocation(line: 759, column: 31, scope: !221)
!587 = !DILocation(line: 760, column: 6, scope: !588)
!588 = distinct !DILexicalBlock(scope: !221, file: !1, line: 760, column: 6)
!589 = !DILocation(line: 760, column: 10, scope: !588)
!590 = !DILocation(line: 760, column: 6, scope: !221)
!591 = !DILocation(line: 761, column: 11, scope: !588)
!592 = !DILocation(line: 761, column: 10, scope: !588)
!593 = !DILocation(line: 761, column: 3, scope: !588)
!594 = !DILocation(line: 762, column: 10, scope: !221)
!595 = !DILocation(line: 762, column: 2, scope: !221)
!596 = !DILocation(line: 763, column: 1, scope: !221)
!597 = !DILocalVariable(name: "a", arg: 1, scope: !218, file: !1, line: 720, type: !4)
!598 = !DILocation(line: 720, column: 49, scope: !218)
!599 = !DILocation(line: 722, column: 32, scope: !218)
!600 = !DILocation(line: 722, column: 10, scope: !218)
!601 = !DILocation(line: 722, column: 2, scope: !218)
!602 = !DILocalVariable(name: "a", arg: 1, scope: !219, file: !1, line: 726, type: !4)
!603 = !DILocation(line: 726, column: 48, scope: !219)
!604 = !DILocalVariable(name: "ustar", scope: !219, file: !1, line: 728, type: !192)
!605 = !DILocation(line: 728, column: 16, scope: !219)
!606 = !DILocation(line: 730, column: 26, scope: !219)
!607 = !DILocation(line: 730, column: 29, scope: !219)
!608 = !DILocation(line: 730, column: 10, scope: !219)
!609 = !DILocation(line: 730, column: 8, scope: !219)
!610 = !DILocation(line: 731, column: 7, scope: !219)
!611 = !DILocation(line: 731, column: 2, scope: !219)
!612 = !DILocation(line: 732, column: 2, scope: !219)
!613 = !DILocation(line: 732, column: 5, scope: !219)
!614 = !DILocation(line: 732, column: 17, scope: !219)
!615 = !DILocation(line: 733, column: 2, scope: !219)
!616 = !DILocalVariable(name: "a", arg: 1, scope: !220, file: !1, line: 737, type: !4)
!617 = !DILocation(line: 737, column: 56, scope: !220)
!618 = !DILocalVariable(name: "ustar", scope: !220, file: !1, line: 739, type: !192)
!619 = !DILocation(line: 739, column: 16, scope: !220)
!620 = !DILocalVariable(name: "ret", scope: !220, file: !1, line: 740, type: !23)
!621 = !DILocation(line: 740, column: 6, scope: !220)
!622 = !DILocation(line: 742, column: 26, scope: !220)
!623 = !DILocation(line: 742, column: 29, scope: !220)
!624 = !DILocation(line: 742, column: 10, scope: !220)
!625 = !DILocation(line: 742, column: 8, scope: !220)
!626 = !DILocation(line: 743, column: 30, scope: !220)
!627 = !DILocation(line: 744, column: 15, scope: !220)
!628 = !DILocation(line: 744, column: 22, scope: !220)
!629 = !DILocation(line: 744, column: 46, scope: !220)
!630 = !DILocation(line: 744, column: 53, scope: !220)
!631 = !DILocation(line: 744, column: 44, scope: !220)
!632 = !DILocation(line: 743, column: 8, scope: !220)
!633 = !DILocation(line: 743, column: 6, scope: !220)
!634 = !DILocation(line: 745, column: 33, scope: !220)
!635 = !DILocation(line: 745, column: 40, scope: !220)
!636 = !DILocation(line: 745, column: 54, scope: !220)
!637 = !DILocation(line: 745, column: 2, scope: !220)
!638 = !DILocation(line: 745, column: 9, scope: !220)
!639 = !DILocation(line: 745, column: 31, scope: !220)
!640 = !DILocation(line: 746, column: 10, scope: !220)
!641 = !DILocation(line: 746, column: 2, scope: !220)
!642 = !DILocalVariable(name: "a", arg: 1, scope: !206, file: !1, line: 386, type: !4)
!643 = !DILocation(line: 386, column: 59, scope: !206)
!644 = !DILocalVariable(name: "h", arg: 2, scope: !206, file: !1, line: 386, type: !95)
!645 = !DILocation(line: 386, column: 67, scope: !206)
!646 = !DILocalVariable(name: "entry", arg: 3, scope: !206, file: !1, line: 387, type: !30)
!647 = !DILocation(line: 387, column: 27, scope: !206)
!648 = !DILocalVariable(name: "tartype", arg: 4, scope: !206, file: !1, line: 387, type: !23)
!649 = !DILocation(line: 387, column: 38, scope: !206)
!650 = !DILocalVariable(name: "strict", arg: 5, scope: !206, file: !1, line: 387, type: !23)
!651 = !DILocation(line: 387, column: 51, scope: !206)
!652 = !DILocalVariable(name: "sconv", arg: 6, scope: !206, file: !1, line: 388, type: !102)
!653 = !DILocation(line: 388, column: 33, scope: !206)
!654 = !DILocalVariable(name: "checksum", scope: !206, file: !1, line: 390, type: !13)
!655 = !DILocation(line: 390, column: 15, scope: !206)
!656 = !DILocalVariable(name: "i", scope: !206, file: !1, line: 391, type: !23)
!657 = !DILocation(line: 391, column: 6, scope: !206)
!658 = !DILocalVariable(name: "r", scope: !206, file: !1, line: 391, type: !23)
!659 = !DILocation(line: 391, column: 9, scope: !206)
!660 = !DILocalVariable(name: "ret", scope: !206, file: !1, line: 391, type: !23)
!661 = !DILocation(line: 391, column: 12, scope: !206)
!662 = !DILocalVariable(name: "copy_length", scope: !206, file: !1, line: 392, type: !45)
!663 = !DILocation(line: 392, column: 9, scope: !206)
!664 = !DILocalVariable(name: "p", scope: !206, file: !1, line: 393, type: !80)
!665 = !DILocation(line: 393, column: 14, scope: !206)
!666 = !DILocalVariable(name: "pp", scope: !206, file: !1, line: 393, type: !80)
!667 = !DILocation(line: 393, column: 18, scope: !206)
!668 = !DILocalVariable(name: "mytartype", scope: !206, file: !1, line: 394, type: !23)
!669 = !DILocation(line: 394, column: 6, scope: !206)
!670 = !DILocation(line: 396, column: 6, scope: !206)
!671 = !DILocation(line: 397, column: 12, scope: !206)
!672 = !DILocation(line: 403, column: 9, scope: !206)
!673 = !DILocation(line: 403, column: 2, scope: !206)
!674 = !DILocation(line: 410, column: 31, scope: !206)
!675 = !DILocation(line: 410, column: 57, scope: !206)
!676 = !DILocation(line: 410, column: 6, scope: !206)
!677 = !DILocation(line: 410, column: 4, scope: !206)
!678 = !DILocation(line: 411, column: 6, scope: !679)
!679 = distinct !DILexicalBlock(scope: !206, file: !1, line: 411, column: 6)
!680 = !DILocation(line: 411, column: 8, scope: !679)
!681 = !DILocation(line: 411, column: 6, scope: !206)
!682 = !DILocation(line: 412, column: 7, scope: !683)
!683 = distinct !DILexicalBlock(scope: !684, file: !1, line: 412, column: 7)
!684 = distinct !DILexicalBlock(scope: !679, file: !1, line: 411, column: 14)
!685 = !DILocation(line: 412, column: 13, scope: !683)
!686 = !DILocation(line: 412, column: 7, scope: !684)
!687 = !DILocation(line: 413, column: 23, scope: !688)
!688 = distinct !DILexicalBlock(scope: !683, file: !1, line: 412, column: 24)
!689 = !DILocation(line: 413, column: 26, scope: !688)
!690 = !DILocation(line: 413, column: 4, scope: !688)
!691 = !DILocation(line: 415, column: 4, scope: !688)
!692 = !DILocation(line: 417, column: 22, scope: !684)
!693 = !DILocation(line: 417, column: 25, scope: !684)
!694 = !DILocation(line: 419, column: 7, scope: !684)
!695 = !DILocation(line: 419, column: 50, scope: !684)
!696 = !DILocation(line: 419, column: 11, scope: !684)
!697 = !DILocation(line: 417, column: 3, scope: !684)
!698 = !DILocation(line: 420, column: 7, scope: !684)
!699 = !DILocation(line: 421, column: 2, scope: !684)
!700 = !DILocation(line: 422, column: 6, scope: !701)
!701 = distinct !DILexicalBlock(scope: !206, file: !1, line: 422, column: 6)
!702 = !DILocation(line: 422, column: 18, scope: !701)
!703 = !DILocation(line: 422, column: 6, scope: !206)
!704 = !DILocation(line: 423, column: 10, scope: !701)
!705 = !DILocation(line: 423, column: 12, scope: !701)
!706 = !DILocation(line: 423, column: 33, scope: !701)
!707 = !DILocation(line: 423, column: 37, scope: !701)
!708 = !DILocation(line: 423, column: 3, scope: !701)
!709 = !DILocation(line: 426, column: 14, scope: !710)
!710 = distinct !DILexicalBlock(scope: !701, file: !1, line: 424, column: 7)
!711 = !DILocation(line: 426, column: 19, scope: !710)
!712 = !DILocation(line: 426, column: 17, scope: !710)
!713 = !DILocation(line: 426, column: 31, scope: !710)
!714 = !DILocation(line: 426, column: 49, scope: !710)
!715 = !DILocation(line: 426, column: 7, scope: !710)
!716 = !DILocation(line: 426, column: 5, scope: !710)
!717 = !DILocation(line: 432, column: 7, scope: !718)
!718 = distinct !DILexicalBlock(scope: !710, file: !1, line: 432, column: 7)
!719 = !DILocation(line: 432, column: 12, scope: !718)
!720 = !DILocation(line: 432, column: 9, scope: !718)
!721 = !DILocation(line: 432, column: 7, scope: !710)
!722 = !DILocation(line: 433, column: 15, scope: !718)
!723 = !DILocation(line: 433, column: 17, scope: !718)
!724 = !DILocation(line: 433, column: 8, scope: !718)
!725 = !DILocation(line: 433, column: 6, scope: !718)
!726 = !DILocation(line: 433, column: 4, scope: !718)
!727 = !DILocation(line: 435, column: 8, scope: !728)
!728 = distinct !DILexicalBlock(scope: !710, file: !1, line: 435, column: 7)
!729 = !DILocation(line: 435, column: 7, scope: !710)
!730 = !DILocation(line: 437, column: 23, scope: !731)
!731 = distinct !DILexicalBlock(scope: !728, file: !1, line: 435, column: 11)
!732 = !DILocation(line: 437, column: 26, scope: !731)
!733 = !DILocation(line: 437, column: 4, scope: !731)
!734 = !DILocation(line: 439, column: 8, scope: !731)
!735 = !DILocation(line: 440, column: 3, scope: !731)
!736 = !DILocation(line: 440, column: 14, scope: !737)
!737 = !DILexicalBlockFile(scope: !738, file: !1, discriminator: 1)
!738 = distinct !DILexicalBlock(scope: !728, file: !1, line: 440, column: 14)
!739 = !DILocation(line: 440, column: 19, scope: !737)
!740 = !DILocation(line: 447, column: 23, scope: !741)
!741 = distinct !DILexicalBlock(scope: !738, file: !1, line: 440, column: 28)
!742 = !DILocation(line: 447, column: 26, scope: !741)
!743 = !DILocation(line: 447, column: 4, scope: !741)
!744 = !DILocation(line: 449, column: 8, scope: !741)
!745 = !DILocation(line: 450, column: 3, scope: !741)
!746 = !DILocation(line: 450, column: 14, scope: !747)
!747 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 1)
!748 = distinct !DILexicalBlock(scope: !738, file: !1, line: 450, column: 14)
!749 = !DILocation(line: 450, column: 19, scope: !747)
!750 = !DILocation(line: 450, column: 22, scope: !747)
!751 = !DILocation(line: 450, column: 17, scope: !747)
!752 = !DILocation(line: 452, column: 23, scope: !753)
!753 = distinct !DILexicalBlock(scope: !748, file: !1, line: 450, column: 43)
!754 = !DILocation(line: 452, column: 26, scope: !753)
!755 = !DILocation(line: 452, column: 4, scope: !753)
!756 = !DILocation(line: 454, column: 8, scope: !753)
!757 = !DILocation(line: 455, column: 3, scope: !753)
!758 = !DILocation(line: 457, column: 11, scope: !759)
!759 = distinct !DILexicalBlock(scope: !748, file: !1, line: 455, column: 10)
!760 = !DILocation(line: 457, column: 13, scope: !759)
!761 = !DILocation(line: 457, column: 36, scope: !759)
!762 = !DILocation(line: 457, column: 40, scope: !759)
!763 = !DILocation(line: 457, column: 44, scope: !759)
!764 = !DILocation(line: 457, column: 42, scope: !759)
!765 = !DILocation(line: 457, column: 4, scope: !759)
!766 = !DILocation(line: 458, column: 11, scope: !759)
!767 = !DILocation(line: 458, column: 13, scope: !759)
!768 = !DILocation(line: 458, column: 34, scope: !759)
!769 = !DILocation(line: 458, column: 36, scope: !759)
!770 = !DILocation(line: 459, column: 8, scope: !759)
!771 = !DILocation(line: 459, column: 13, scope: !759)
!772 = !DILocation(line: 459, column: 11, scope: !759)
!773 = !DILocation(line: 459, column: 27, scope: !759)
!774 = !DILocation(line: 459, column: 25, scope: !759)
!775 = !DILocation(line: 459, column: 29, scope: !759)
!776 = !DILocation(line: 458, column: 4, scope: !759)
!777 = !DILocation(line: 463, column: 31, scope: !206)
!778 = !DILocation(line: 463, column: 56, scope: !206)
!779 = !DILocation(line: 463, column: 6, scope: !206)
!780 = !DILocation(line: 463, column: 4, scope: !206)
!781 = !DILocation(line: 464, column: 6, scope: !782)
!782 = distinct !DILexicalBlock(scope: !206, file: !1, line: 464, column: 6)
!783 = !DILocation(line: 464, column: 8, scope: !782)
!784 = !DILocation(line: 464, column: 6, scope: !206)
!785 = !DILocation(line: 465, column: 7, scope: !786)
!786 = distinct !DILexicalBlock(scope: !787, file: !1, line: 465, column: 7)
!787 = distinct !DILexicalBlock(scope: !782, file: !1, line: 464, column: 14)
!788 = !DILocation(line: 465, column: 13, scope: !786)
!789 = !DILocation(line: 465, column: 7, scope: !787)
!790 = !DILocation(line: 466, column: 23, scope: !791)
!791 = distinct !DILexicalBlock(scope: !786, file: !1, line: 465, column: 24)
!792 = !DILocation(line: 466, column: 26, scope: !791)
!793 = !DILocation(line: 466, column: 4, scope: !791)
!794 = !DILocation(line: 468, column: 4, scope: !791)
!795 = !DILocation(line: 470, column: 22, scope: !787)
!796 = !DILocation(line: 470, column: 25, scope: !787)
!797 = !DILocation(line: 473, column: 7, scope: !787)
!798 = !DILocation(line: 473, column: 49, scope: !787)
!799 = !DILocation(line: 473, column: 10, scope: !787)
!800 = !DILocation(line: 470, column: 3, scope: !787)
!801 = !DILocation(line: 474, column: 7, scope: !787)
!802 = !DILocation(line: 475, column: 2, scope: !787)
!803 = !DILocation(line: 476, column: 6, scope: !804)
!804 = distinct !DILexicalBlock(scope: !206, file: !1, line: 476, column: 6)
!805 = !DILocation(line: 476, column: 18, scope: !804)
!806 = !DILocation(line: 476, column: 6, scope: !206)
!807 = !DILocation(line: 477, column: 13, scope: !804)
!808 = !DILocation(line: 477, column: 3, scope: !804)
!809 = !DILocation(line: 479, column: 31, scope: !810)
!810 = distinct !DILexicalBlock(scope: !804, file: !1, line: 478, column: 7)
!811 = !DILocation(line: 479, column: 56, scope: !810)
!812 = !DILocation(line: 479, column: 7, scope: !810)
!813 = !DILocation(line: 479, column: 5, scope: !810)
!814 = !DILocation(line: 480, column: 7, scope: !815)
!815 = distinct !DILexicalBlock(scope: !810, file: !1, line: 480, column: 7)
!816 = !DILocation(line: 480, column: 9, scope: !815)
!817 = !DILocation(line: 480, column: 7, scope: !810)
!818 = !DILocation(line: 481, column: 8, scope: !819)
!819 = distinct !DILexicalBlock(scope: !820, file: !1, line: 481, column: 8)
!820 = distinct !DILexicalBlock(scope: !815, file: !1, line: 480, column: 15)
!821 = !DILocation(line: 481, column: 14, scope: !819)
!822 = !DILocation(line: 481, column: 8, scope: !820)
!823 = !DILocation(line: 482, column: 24, scope: !824)
!824 = distinct !DILexicalBlock(scope: !819, file: !1, line: 481, column: 25)
!825 = !DILocation(line: 482, column: 27, scope: !824)
!826 = !DILocation(line: 482, column: 5, scope: !824)
!827 = !DILocation(line: 484, column: 5, scope: !824)
!828 = !DILocation(line: 486, column: 23, scope: !820)
!829 = !DILocation(line: 486, column: 26, scope: !820)
!830 = !DILocation(line: 489, column: 8, scope: !820)
!831 = !DILocation(line: 489, column: 50, scope: !820)
!832 = !DILocation(line: 489, column: 11, scope: !820)
!833 = !DILocation(line: 486, column: 4, scope: !820)
!834 = !DILocation(line: 490, column: 8, scope: !820)
!835 = !DILocation(line: 491, column: 3, scope: !820)
!836 = !DILocation(line: 493, column: 6, scope: !837)
!837 = distinct !DILexicalBlock(scope: !206, file: !1, line: 493, column: 6)
!838 = !DILocation(line: 493, column: 18, scope: !837)
!839 = !DILocation(line: 493, column: 6, scope: !206)
!840 = !DILocation(line: 494, column: 7, scope: !841)
!841 = distinct !DILexicalBlock(scope: !842, file: !1, line: 494, column: 7)
!842 = distinct !DILexicalBlock(scope: !837, file: !1, line: 493, column: 23)
!843 = !DILocation(line: 494, column: 19, scope: !841)
!844 = !DILocation(line: 494, column: 7, scope: !842)
!845 = !DILocation(line: 495, column: 23, scope: !846)
!846 = distinct !DILexicalBlock(scope: !841, file: !1, line: 494, column: 42)
!847 = !DILocation(line: 495, column: 26, scope: !846)
!848 = !DILocation(line: 495, column: 4, scope: !846)
!849 = !DILocation(line: 497, column: 8, scope: !846)
!850 = !DILocation(line: 498, column: 16, scope: !846)
!851 = !DILocation(line: 499, column: 3, scope: !846)
!852 = !DILocation(line: 500, column: 10, scope: !842)
!853 = !DILocation(line: 500, column: 12, scope: !842)
!854 = !DILocation(line: 500, column: 37, scope: !842)
!855 = !DILocation(line: 500, column: 40, scope: !842)
!856 = !DILocation(line: 500, column: 3, scope: !842)
!857 = !DILocation(line: 501, column: 2, scope: !842)
!858 = !DILocation(line: 503, column: 28, scope: !206)
!859 = !DILocation(line: 503, column: 53, scope: !206)
!860 = !DILocation(line: 503, column: 6, scope: !206)
!861 = !DILocation(line: 503, column: 4, scope: !206)
!862 = !DILocation(line: 504, column: 6, scope: !863)
!863 = distinct !DILexicalBlock(scope: !206, file: !1, line: 504, column: 6)
!864 = !DILocation(line: 504, column: 8, scope: !863)
!865 = !DILocation(line: 504, column: 6, scope: !206)
!866 = !DILocation(line: 505, column: 7, scope: !867)
!867 = distinct !DILexicalBlock(scope: !868, file: !1, line: 505, column: 7)
!868 = distinct !DILexicalBlock(scope: !863, file: !1, line: 504, column: 14)
!869 = !DILocation(line: 505, column: 13, scope: !867)
!870 = !DILocation(line: 505, column: 7, scope: !868)
!871 = !DILocation(line: 506, column: 23, scope: !872)
!872 = distinct !DILexicalBlock(scope: !867, file: !1, line: 505, column: 24)
!873 = !DILocation(line: 506, column: 26, scope: !872)
!874 = !DILocation(line: 506, column: 4, scope: !872)
!875 = !DILocation(line: 508, column: 4, scope: !872)
!876 = !DILocation(line: 510, column: 22, scope: !868)
!877 = !DILocation(line: 510, column: 25, scope: !868)
!878 = !DILocation(line: 513, column: 7, scope: !868)
!879 = !DILocation(line: 513, column: 49, scope: !868)
!880 = !DILocation(line: 513, column: 10, scope: !868)
!881 = !DILocation(line: 510, column: 3, scope: !868)
!882 = !DILocation(line: 514, column: 7, scope: !868)
!883 = !DILocation(line: 515, column: 2, scope: !868)
!884 = !DILocation(line: 516, column: 6, scope: !885)
!885 = distinct !DILexicalBlock(scope: !206, file: !1, line: 516, column: 6)
!886 = !DILocation(line: 516, column: 18, scope: !885)
!887 = !DILocation(line: 516, column: 6, scope: !206)
!888 = !DILocation(line: 517, column: 7, scope: !889)
!889 = distinct !DILexicalBlock(scope: !890, file: !1, line: 517, column: 7)
!890 = distinct !DILexicalBlock(scope: !885, file: !1, line: 516, column: 23)
!891 = !DILocation(line: 517, column: 19, scope: !889)
!892 = !DILocation(line: 517, column: 7, scope: !890)
!893 = !DILocation(line: 518, column: 23, scope: !894)
!894 = distinct !DILexicalBlock(scope: !889, file: !1, line: 517, column: 39)
!895 = !DILocation(line: 518, column: 26, scope: !894)
!896 = !DILocation(line: 518, column: 4, scope: !894)
!897 = !DILocation(line: 520, column: 8, scope: !894)
!898 = !DILocation(line: 521, column: 16, scope: !894)
!899 = !DILocation(line: 522, column: 3, scope: !894)
!900 = !DILocation(line: 523, column: 10, scope: !890)
!901 = !DILocation(line: 523, column: 12, scope: !890)
!902 = !DILocation(line: 523, column: 34, scope: !890)
!903 = !DILocation(line: 523, column: 37, scope: !890)
!904 = !DILocation(line: 523, column: 3, scope: !890)
!905 = !DILocation(line: 524, column: 2, scope: !890)
!906 = !DILocation(line: 526, column: 28, scope: !206)
!907 = !DILocation(line: 526, column: 53, scope: !206)
!908 = !DILocation(line: 526, column: 6, scope: !206)
!909 = !DILocation(line: 526, column: 4, scope: !206)
!910 = !DILocation(line: 527, column: 6, scope: !911)
!911 = distinct !DILexicalBlock(scope: !206, file: !1, line: 527, column: 6)
!912 = !DILocation(line: 527, column: 8, scope: !911)
!913 = !DILocation(line: 527, column: 6, scope: !206)
!914 = !DILocation(line: 528, column: 7, scope: !915)
!915 = distinct !DILexicalBlock(scope: !916, file: !1, line: 528, column: 7)
!916 = distinct !DILexicalBlock(scope: !911, file: !1, line: 527, column: 14)
!917 = !DILocation(line: 528, column: 13, scope: !915)
!918 = !DILocation(line: 528, column: 7, scope: !916)
!919 = !DILocation(line: 529, column: 23, scope: !920)
!920 = distinct !DILexicalBlock(scope: !915, file: !1, line: 528, column: 24)
!921 = !DILocation(line: 529, column: 26, scope: !920)
!922 = !DILocation(line: 529, column: 4, scope: !920)
!923 = !DILocation(line: 531, column: 4, scope: !920)
!924 = !DILocation(line: 533, column: 22, scope: !916)
!925 = !DILocation(line: 533, column: 25, scope: !916)
!926 = !DILocation(line: 536, column: 7, scope: !916)
!927 = !DILocation(line: 536, column: 49, scope: !916)
!928 = !DILocation(line: 536, column: 10, scope: !916)
!929 = !DILocation(line: 533, column: 3, scope: !916)
!930 = !DILocation(line: 537, column: 7, scope: !916)
!931 = !DILocation(line: 538, column: 2, scope: !916)
!932 = !DILocation(line: 539, column: 6, scope: !933)
!933 = distinct !DILexicalBlock(scope: !206, file: !1, line: 539, column: 6)
!934 = !DILocation(line: 539, column: 18, scope: !933)
!935 = !DILocation(line: 539, column: 6, scope: !206)
!936 = !DILocation(line: 540, column: 14, scope: !937)
!937 = distinct !DILexicalBlock(scope: !938, file: !1, line: 540, column: 7)
!938 = distinct !DILexicalBlock(scope: !933, file: !1, line: 539, column: 23)
!939 = !DILocation(line: 540, column: 7, scope: !937)
!940 = !DILocation(line: 540, column: 17, scope: !937)
!941 = !DILocation(line: 540, column: 7, scope: !938)
!942 = !DILocation(line: 541, column: 23, scope: !943)
!943 = distinct !DILexicalBlock(scope: !937, file: !1, line: 540, column: 37)
!944 = !DILocation(line: 541, column: 26, scope: !943)
!945 = !DILocation(line: 541, column: 4, scope: !943)
!946 = !DILocation(line: 543, column: 8, scope: !943)
!947 = !DILocation(line: 544, column: 16, scope: !943)
!948 = !DILocation(line: 545, column: 3, scope: !943)
!949 = !DILocation(line: 546, column: 10, scope: !938)
!950 = !DILocation(line: 546, column: 12, scope: !938)
!951 = !DILocation(line: 546, column: 34, scope: !938)
!952 = !DILocation(line: 546, column: 37, scope: !938)
!953 = !DILocation(line: 546, column: 3, scope: !938)
!954 = !DILocation(line: 547, column: 2, scope: !938)
!955 = !DILocation(line: 549, column: 39, scope: !956)
!956 = distinct !DILexicalBlock(scope: !206, file: !1, line: 549, column: 6)
!957 = !DILocation(line: 549, column: 20, scope: !956)
!958 = !DILocation(line: 549, column: 46, scope: !956)
!959 = !DILocation(line: 550, column: 6, scope: !956)
!960 = !DILocation(line: 550, column: 8, scope: !956)
!961 = !DILocation(line: 550, column: 67, scope: !956)
!962 = !DILocation(line: 549, column: 6, scope: !963)
!963 = !DILexicalBlockFile(scope: !956, file: !1, discriminator: 1)
!964 = !DILocation(line: 549, column: 6, scope: !956)
!965 = !DILocation(line: 549, column: 6, scope: !206)
!966 = !DILocation(line: 551, column: 22, scope: !967)
!967 = distinct !DILexicalBlock(scope: !956, file: !1, line: 550, column: 76)
!968 = !DILocation(line: 551, column: 25, scope: !967)
!969 = !DILocation(line: 551, column: 3, scope: !967)
!970 = !DILocation(line: 553, column: 7, scope: !967)
!971 = !DILocation(line: 554, column: 2, scope: !967)
!972 = !DILocation(line: 556, column: 38, scope: !973)
!973 = distinct !DILexicalBlock(scope: !206, file: !1, line: 556, column: 6)
!974 = !DILocation(line: 556, column: 20, scope: !973)
!975 = !DILocation(line: 557, column: 6, scope: !973)
!976 = !DILocation(line: 557, column: 8, scope: !973)
!977 = !DILocation(line: 557, column: 64, scope: !973)
!978 = !DILocation(line: 556, column: 6, scope: !979)
!979 = !DILexicalBlockFile(scope: !973, file: !1, discriminator: 1)
!980 = !DILocation(line: 556, column: 6, scope: !973)
!981 = !DILocation(line: 556, column: 6, scope: !206)
!982 = !DILocation(line: 558, column: 22, scope: !983)
!983 = distinct !DILexicalBlock(scope: !973, file: !1, line: 557, column: 73)
!984 = !DILocation(line: 558, column: 25, scope: !983)
!985 = !DILocation(line: 558, column: 3, scope: !983)
!986 = !DILocation(line: 560, column: 7, scope: !983)
!987 = !DILocation(line: 561, column: 2, scope: !983)
!988 = !DILocation(line: 563, column: 38, scope: !989)
!989 = distinct !DILexicalBlock(scope: !206, file: !1, line: 563, column: 6)
!990 = !DILocation(line: 563, column: 20, scope: !989)
!991 = !DILocation(line: 564, column: 6, scope: !989)
!992 = !DILocation(line: 564, column: 8, scope: !989)
!993 = !DILocation(line: 564, column: 64, scope: !989)
!994 = !DILocation(line: 563, column: 6, scope: !995)
!995 = !DILexicalBlockFile(scope: !989, file: !1, discriminator: 1)
!996 = !DILocation(line: 563, column: 6, scope: !989)
!997 = !DILocation(line: 563, column: 6, scope: !206)
!998 = !DILocation(line: 565, column: 22, scope: !999)
!999 = distinct !DILexicalBlock(scope: !989, file: !1, line: 564, column: 73)
!1000 = !DILocation(line: 565, column: 25, scope: !999)
!1001 = !DILocation(line: 565, column: 3, scope: !999)
!1002 = !DILocation(line: 567, column: 7, scope: !999)
!1003 = !DILocation(line: 568, column: 2, scope: !999)
!1004 = !DILocation(line: 570, column: 39, scope: !1005)
!1005 = distinct !DILexicalBlock(scope: !206, file: !1, line: 570, column: 6)
!1006 = !DILocation(line: 570, column: 20, scope: !1005)
!1007 = !DILocation(line: 571, column: 6, scope: !1005)
!1008 = !DILocation(line: 571, column: 8, scope: !1005)
!1009 = !DILocation(line: 571, column: 67, scope: !1005)
!1010 = !DILocation(line: 570, column: 6, scope: !1011)
!1011 = !DILexicalBlockFile(scope: !1005, file: !1, discriminator: 1)
!1012 = !DILocation(line: 570, column: 6, scope: !1005)
!1013 = !DILocation(line: 570, column: 6, scope: !206)
!1014 = !DILocation(line: 572, column: 22, scope: !1015)
!1015 = distinct !DILexicalBlock(scope: !1005, file: !1, line: 571, column: 76)
!1016 = !DILocation(line: 572, column: 25, scope: !1015)
!1017 = !DILocation(line: 572, column: 3, scope: !1015)
!1018 = !DILocation(line: 574, column: 7, scope: !1015)
!1019 = !DILocation(line: 575, column: 2, scope: !1015)
!1020 = !DILocation(line: 577, column: 40, scope: !1021)
!1021 = distinct !DILexicalBlock(scope: !206, file: !1, line: 577, column: 6)
!1022 = !DILocation(line: 577, column: 20, scope: !1021)
!1023 = !DILocation(line: 578, column: 6, scope: !1021)
!1024 = !DILocation(line: 578, column: 8, scope: !1021)
!1025 = !DILocation(line: 578, column: 70, scope: !1021)
!1026 = !DILocation(line: 577, column: 6, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1021, file: !1, discriminator: 1)
!1028 = !DILocation(line: 577, column: 6, scope: !1021)
!1029 = !DILocation(line: 577, column: 6, scope: !206)
!1030 = !DILocation(line: 579, column: 22, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !1021, file: !1, line: 578, column: 79)
!1032 = !DILocation(line: 579, column: 25, scope: !1031)
!1033 = !DILocation(line: 579, column: 3, scope: !1031)
!1034 = !DILocation(line: 581, column: 7, scope: !1031)
!1035 = !DILocation(line: 582, column: 2, scope: !1031)
!1036 = !DILocation(line: 584, column: 29, scope: !1037)
!1037 = distinct !DILexicalBlock(scope: !206, file: !1, line: 584, column: 6)
!1038 = !DILocation(line: 584, column: 6, scope: !1037)
!1039 = !DILocation(line: 584, column: 36, scope: !1037)
!1040 = !DILocation(line: 585, column: 6, scope: !1037)
!1041 = !DILocation(line: 585, column: 32, scope: !1042)
!1042 = !DILexicalBlockFile(scope: !1037, file: !1, discriminator: 1)
!1043 = !DILocation(line: 585, column: 9, scope: !1042)
!1044 = !DILocation(line: 585, column: 39, scope: !1042)
!1045 = !DILocation(line: 584, column: 6, scope: !1046)
!1046 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 1)
!1047 = !DILocation(line: 586, column: 45, scope: !1048)
!1048 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 586, column: 7)
!1049 = distinct !DILexicalBlock(scope: !1037, file: !1, line: 585, column: 52)
!1050 = !DILocation(line: 586, column: 21, scope: !1048)
!1051 = !DILocation(line: 587, column: 7, scope: !1048)
!1052 = !DILocation(line: 587, column: 9, scope: !1048)
!1053 = !DILocation(line: 588, column: 33, scope: !1048)
!1054 = !DILocation(line: 586, column: 7, scope: !1055)
!1055 = !DILexicalBlockFile(scope: !1048, file: !1, discriminator: 1)
!1056 = !DILocation(line: 586, column: 7, scope: !1048)
!1057 = !DILocation(line: 586, column: 7, scope: !1049)
!1058 = !DILocation(line: 589, column: 23, scope: !1059)
!1059 = distinct !DILexicalBlock(scope: !1048, file: !1, line: 588, column: 42)
!1060 = !DILocation(line: 589, column: 26, scope: !1059)
!1061 = !DILocation(line: 589, column: 4, scope: !1059)
!1062 = !DILocation(line: 591, column: 8, scope: !1059)
!1063 = !DILocation(line: 592, column: 3, scope: !1059)
!1064 = !DILocation(line: 594, column: 45, scope: !1065)
!1065 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 594, column: 7)
!1066 = !DILocation(line: 594, column: 21, scope: !1065)
!1067 = !DILocation(line: 595, column: 7, scope: !1065)
!1068 = !DILocation(line: 595, column: 9, scope: !1065)
!1069 = !DILocation(line: 596, column: 33, scope: !1065)
!1070 = !DILocation(line: 594, column: 7, scope: !1071)
!1071 = !DILexicalBlockFile(scope: !1065, file: !1, discriminator: 1)
!1072 = !DILocation(line: 594, column: 7, scope: !1065)
!1073 = !DILocation(line: 594, column: 7, scope: !1049)
!1074 = !DILocation(line: 597, column: 23, scope: !1075)
!1075 = distinct !DILexicalBlock(scope: !1065, file: !1, line: 596, column: 42)
!1076 = !DILocation(line: 597, column: 26, scope: !1075)
!1077 = !DILocation(line: 597, column: 4, scope: !1075)
!1078 = !DILocation(line: 599, column: 8, scope: !1075)
!1079 = !DILocation(line: 600, column: 3, scope: !1075)
!1080 = !DILocation(line: 601, column: 2, scope: !1049)
!1081 = !DILocation(line: 603, column: 6, scope: !1082)
!1082 = distinct !DILexicalBlock(scope: !206, file: !1, line: 603, column: 6)
!1083 = !DILocation(line: 603, column: 14, scope: !1082)
!1084 = !DILocation(line: 603, column: 6, scope: !206)
!1085 = !DILocation(line: 604, column: 30, scope: !1086)
!1086 = distinct !DILexicalBlock(scope: !1082, file: !1, line: 603, column: 20)
!1087 = !DILocation(line: 604, column: 3, scope: !1086)
!1088 = !DILocation(line: 604, column: 28, scope: !1086)
!1089 = !DILocation(line: 605, column: 2, scope: !1086)
!1090 = !DILocation(line: 605, column: 13, scope: !1091)
!1091 = !DILexicalBlockFile(scope: !1092, file: !1, discriminator: 1)
!1092 = distinct !DILexicalBlock(scope: !1082, file: !1, line: 605, column: 13)
!1093 = !DILocation(line: 605, column: 23, scope: !1091)
!1094 = !DILocation(line: 606, column: 30, scope: !1095)
!1095 = distinct !DILexicalBlock(scope: !1092, file: !1, line: 605, column: 29)
!1096 = !DILocation(line: 606, column: 3, scope: !1095)
!1097 = !DILocation(line: 606, column: 28, scope: !1095)
!1098 = !DILocation(line: 607, column: 2, scope: !1095)
!1099 = !DILocation(line: 608, column: 34, scope: !1100)
!1100 = distinct !DILexicalBlock(scope: !1092, file: !1, line: 607, column: 9)
!1101 = !DILocation(line: 608, column: 11, scope: !1100)
!1102 = !DILocation(line: 608, column: 3, scope: !1100)
!1103 = !DILocation(line: 609, column: 18, scope: !1104)
!1104 = distinct !DILexicalBlock(scope: !1100, file: !1, line: 608, column: 42)
!1105 = !DILocation(line: 609, column: 43, scope: !1104)
!1106 = !DILocation(line: 609, column: 51, scope: !1104)
!1107 = !DILocation(line: 610, column: 18, scope: !1104)
!1108 = !DILocation(line: 610, column: 43, scope: !1104)
!1109 = !DILocation(line: 610, column: 51, scope: !1104)
!1110 = !DILocation(line: 611, column: 18, scope: !1104)
!1111 = !DILocation(line: 611, column: 43, scope: !1104)
!1112 = !DILocation(line: 611, column: 51, scope: !1104)
!1113 = !DILocation(line: 612, column: 18, scope: !1104)
!1114 = !DILocation(line: 612, column: 43, scope: !1104)
!1115 = !DILocation(line: 612, column: 51, scope: !1104)
!1116 = !DILocation(line: 613, column: 18, scope: !1104)
!1117 = !DILocation(line: 613, column: 43, scope: !1104)
!1118 = !DILocation(line: 613, column: 51, scope: !1104)
!1119 = !DILocation(line: 614, column: 18, scope: !1104)
!1120 = !DILocation(line: 614, column: 43, scope: !1104)
!1121 = !DILocation(line: 614, column: 51, scope: !1104)
!1122 = !DILocation(line: 616, column: 23, scope: !1104)
!1123 = !DILocation(line: 616, column: 26, scope: !1104)
!1124 = !DILocation(line: 616, column: 4, scope: !1104)
!1125 = !DILocation(line: 619, column: 4, scope: !1104)
!1126 = !DILocation(line: 621, column: 23, scope: !1104)
!1127 = !DILocation(line: 621, column: 26, scope: !1104)
!1128 = !DILocation(line: 624, column: 42, scope: !1104)
!1129 = !DILocation(line: 624, column: 23, scope: !1104)
!1130 = !DILocation(line: 624, column: 8, scope: !1104)
!1131 = !DILocation(line: 621, column: 4, scope: !1104)
!1132 = !DILocation(line: 625, column: 8, scope: !1104)
!1133 = !DILocation(line: 626, column: 3, scope: !1104)
!1134 = !DILocation(line: 629, column: 11, scope: !206)
!1135 = !DILocation(line: 630, column: 9, scope: !1136)
!1136 = distinct !DILexicalBlock(scope: !206, file: !1, line: 630, column: 2)
!1137 = !DILocation(line: 630, column: 7, scope: !1136)
!1138 = !DILocation(line: 630, column: 14, scope: !1139)
!1139 = !DILexicalBlockFile(scope: !1140, file: !1, discriminator: 1)
!1140 = distinct !DILexicalBlock(scope: !1136, file: !1, line: 630, column: 2)
!1141 = !DILocation(line: 630, column: 16, scope: !1139)
!1142 = !DILocation(line: 630, column: 2, scope: !1139)
!1143 = !DILocation(line: 631, column: 37, scope: !1140)
!1144 = !DILocation(line: 631, column: 35, scope: !1140)
!1145 = !DILocation(line: 631, column: 21, scope: !1140)
!1146 = !DILocation(line: 631, column: 19, scope: !1140)
!1147 = !DILocation(line: 631, column: 12, scope: !1140)
!1148 = !DILocation(line: 631, column: 3, scope: !1140)
!1149 = !DILocation(line: 630, column: 24, scope: !1150)
!1150 = !DILexicalBlockFile(scope: !1140, file: !1, discriminator: 2)
!1151 = !DILocation(line: 630, column: 2, scope: !1150)
!1152 = !DILocation(line: 632, column: 2, scope: !206)
!1153 = !DILocation(line: 632, column: 31, scope: !206)
!1154 = !DILocation(line: 634, column: 15, scope: !206)
!1155 = !DILocation(line: 634, column: 25, scope: !206)
!1156 = !DILocation(line: 634, column: 27, scope: !206)
!1157 = !DILocation(line: 634, column: 2, scope: !206)
!1158 = !DILocation(line: 635, column: 10, scope: !206)
!1159 = !DILocation(line: 635, column: 2, scope: !206)
!1160 = !DILocation(line: 636, column: 1, scope: !206)
!1161 = !DILocalVariable(name: "v", arg: 1, scope: !211, file: !1, line: 642, type: !52)
!1162 = !DILocation(line: 642, column: 23, scope: !211)
!1163 = !DILocalVariable(name: "p", arg: 2, scope: !211, file: !1, line: 642, type: !95)
!1164 = !DILocation(line: 642, column: 32, scope: !211)
!1165 = !DILocalVariable(name: "s", arg: 3, scope: !211, file: !1, line: 642, type: !23)
!1166 = !DILocation(line: 642, column: 39, scope: !211)
!1167 = !DILocalVariable(name: "maxsize", arg: 4, scope: !211, file: !1, line: 642, type: !23)
!1168 = !DILocation(line: 642, column: 46, scope: !211)
!1169 = !DILocalVariable(name: "strict", arg: 5, scope: !211, file: !1, line: 642, type: !23)
!1170 = !DILocation(line: 642, column: 59, scope: !211)
!1171 = !DILocalVariable(name: "limit", scope: !211, file: !1, line: 644, type: !52)
!1172 = !DILocation(line: 644, column: 10, scope: !211)
!1173 = !DILocation(line: 646, column: 26, scope: !211)
!1174 = !DILocation(line: 646, column: 27, scope: !211)
!1175 = !DILocation(line: 646, column: 22, scope: !211)
!1176 = !DILocation(line: 646, column: 8, scope: !211)
!1177 = !DILocation(line: 649, column: 6, scope: !1178)
!1178 = distinct !DILexicalBlock(scope: !211, file: !1, line: 649, column: 6)
!1179 = !DILocation(line: 649, column: 6, scope: !211)
!1180 = !DILocation(line: 650, column: 24, scope: !1178)
!1181 = !DILocation(line: 650, column: 27, scope: !1178)
!1182 = !DILocation(line: 650, column: 30, scope: !1178)
!1183 = !DILocation(line: 650, column: 11, scope: !1178)
!1184 = !DILocation(line: 650, column: 3, scope: !1178)
!1185 = !DILocation(line: 658, column: 6, scope: !1186)
!1186 = distinct !DILexicalBlock(scope: !211, file: !1, line: 658, column: 6)
!1187 = !DILocation(line: 658, column: 8, scope: !1186)
!1188 = !DILocation(line: 658, column: 6, scope: !211)
!1189 = !DILocation(line: 659, column: 3, scope: !1190)
!1190 = distinct !DILexicalBlock(scope: !1186, file: !1, line: 658, column: 14)
!1191 = !DILocation(line: 659, column: 10, scope: !1192)
!1192 = !DILexicalBlockFile(scope: !1190, file: !1, discriminator: 1)
!1193 = !DILocation(line: 659, column: 15, scope: !1192)
!1194 = !DILocation(line: 659, column: 12, scope: !1192)
!1195 = !DILocation(line: 659, column: 3, scope: !1192)
!1196 = !DILocation(line: 660, column: 8, scope: !1197)
!1197 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 660, column: 8)
!1198 = distinct !DILexicalBlock(scope: !1190, file: !1, line: 659, column: 24)
!1199 = !DILocation(line: 660, column: 12, scope: !1197)
!1200 = !DILocation(line: 660, column: 10, scope: !1197)
!1201 = !DILocation(line: 660, column: 8, scope: !1198)
!1202 = !DILocation(line: 661, column: 26, scope: !1197)
!1203 = !DILocation(line: 661, column: 29, scope: !1197)
!1204 = !DILocation(line: 661, column: 32, scope: !1197)
!1205 = !DILocation(line: 661, column: 13, scope: !1197)
!1206 = !DILocation(line: 661, column: 5, scope: !1197)
!1207 = !DILocation(line: 662, column: 5, scope: !1198)
!1208 = !DILocation(line: 663, column: 10, scope: !1198)
!1209 = !DILocation(line: 659, column: 3, scope: !1210)
!1210 = !DILexicalBlockFile(scope: !1190, file: !1, discriminator: 2)
!1211 = !DILocation(line: 665, column: 2, scope: !1190)
!1212 = !DILocation(line: 668, column: 21, scope: !211)
!1213 = !DILocation(line: 668, column: 24, scope: !211)
!1214 = !DILocation(line: 668, column: 27, scope: !211)
!1215 = !DILocation(line: 668, column: 10, scope: !211)
!1216 = !DILocation(line: 668, column: 2, scope: !211)
!1217 = !DILocation(line: 669, column: 1, scope: !211)
!1218 = !DILocalVariable(name: "v", arg: 1, scope: !217, file: !1, line: 690, type: !52)
!1219 = !DILocation(line: 690, column: 22, scope: !217)
!1220 = !DILocalVariable(name: "p", arg: 2, scope: !217, file: !1, line: 690, type: !95)
!1221 = !DILocation(line: 690, column: 31, scope: !217)
!1222 = !DILocalVariable(name: "s", arg: 3, scope: !217, file: !1, line: 690, type: !23)
!1223 = !DILocation(line: 690, column: 38, scope: !217)
!1224 = !DILocalVariable(name: "len", scope: !217, file: !1, line: 692, type: !23)
!1225 = !DILocation(line: 692, column: 6, scope: !217)
!1226 = !DILocation(line: 694, column: 8, scope: !217)
!1227 = !DILocation(line: 694, column: 6, scope: !217)
!1228 = !DILocation(line: 697, column: 6, scope: !1229)
!1229 = distinct !DILexicalBlock(scope: !217, file: !1, line: 697, column: 6)
!1230 = !DILocation(line: 697, column: 8, scope: !1229)
!1231 = !DILocation(line: 697, column: 6, scope: !217)
!1232 = !DILocation(line: 698, column: 3, scope: !1233)
!1233 = distinct !DILexicalBlock(scope: !1229, file: !1, line: 697, column: 13)
!1234 = !DILocation(line: 698, column: 13, scope: !1235)
!1235 = !DILexicalBlockFile(scope: !1233, file: !1, discriminator: 1)
!1236 = !DILocation(line: 698, column: 16, scope: !1235)
!1237 = !DILocation(line: 698, column: 3, scope: !1235)
!1238 = !DILocation(line: 699, column: 6, scope: !1233)
!1239 = !DILocation(line: 699, column: 9, scope: !1233)
!1240 = !DILocation(line: 698, column: 3, scope: !1241)
!1241 = !DILexicalBlockFile(scope: !1233, file: !1, discriminator: 2)
!1242 = !DILocation(line: 700, column: 3, scope: !1233)
!1243 = !DILocation(line: 703, column: 7, scope: !217)
!1244 = !DILocation(line: 703, column: 4, scope: !217)
!1245 = !DILocation(line: 704, column: 2, scope: !217)
!1246 = !DILocation(line: 704, column: 10, scope: !1247)
!1247 = !DILexicalBlockFile(scope: !217, file: !1, discriminator: 1)
!1248 = !DILocation(line: 704, column: 13, scope: !1247)
!1249 = !DILocation(line: 704, column: 2, scope: !1247)
!1250 = !DILocation(line: 705, column: 24, scope: !1251)
!1251 = distinct !DILexicalBlock(scope: !217, file: !1, line: 704, column: 18)
!1252 = !DILocation(line: 705, column: 26, scope: !1251)
!1253 = !DILocation(line: 705, column: 21, scope: !1251)
!1254 = !DILocation(line: 705, column: 10, scope: !1251)
!1255 = !DILocation(line: 705, column: 4, scope: !1251)
!1256 = !DILocation(line: 705, column: 8, scope: !1251)
!1257 = !DILocation(line: 706, column: 5, scope: !1251)
!1258 = !DILocation(line: 704, column: 2, scope: !1259)
!1259 = !DILexicalBlockFile(scope: !217, file: !1, discriminator: 2)
!1260 = !DILocation(line: 709, column: 6, scope: !1261)
!1261 = distinct !DILexicalBlock(scope: !217, file: !1, line: 709, column: 6)
!1262 = !DILocation(line: 709, column: 8, scope: !1261)
!1263 = !DILocation(line: 709, column: 6, scope: !217)
!1264 = !DILocation(line: 710, column: 3, scope: !1261)
!1265 = !DILocation(line: 713, column: 2, scope: !217)
!1266 = !DILocation(line: 713, column: 12, scope: !1247)
!1267 = !DILocation(line: 713, column: 15, scope: !1247)
!1268 = !DILocation(line: 713, column: 2, scope: !1247)
!1269 = !DILocation(line: 714, column: 5, scope: !217)
!1270 = !DILocation(line: 714, column: 8, scope: !217)
!1271 = !DILocation(line: 713, column: 2, scope: !1259)
!1272 = !DILocation(line: 716, column: 2, scope: !217)
!1273 = !DILocation(line: 717, column: 1, scope: !217)
!1274 = !DILocalVariable(name: "v", arg: 1, scope: !214, file: !1, line: 675, type: !52)
!1275 = !DILocation(line: 675, column: 20, scope: !214)
!1276 = !DILocalVariable(name: "p", arg: 2, scope: !214, file: !1, line: 675, type: !95)
!1277 = !DILocation(line: 675, column: 29, scope: !214)
!1278 = !DILocalVariable(name: "s", arg: 3, scope: !214, file: !1, line: 675, type: !23)
!1279 = !DILocation(line: 675, column: 36, scope: !214)
!1280 = !DILocation(line: 677, column: 7, scope: !214)
!1281 = !DILocation(line: 677, column: 4, scope: !214)
!1282 = !DILocation(line: 678, column: 2, scope: !214)
!1283 = !DILocation(line: 678, column: 10, scope: !1284)
!1284 = !DILexicalBlockFile(scope: !214, file: !1, discriminator: 1)
!1285 = !DILocation(line: 678, column: 13, scope: !1284)
!1286 = !DILocation(line: 678, column: 2, scope: !1284)
!1287 = !DILocation(line: 679, column: 17, scope: !1288)
!1288 = distinct !DILexicalBlock(scope: !214, file: !1, line: 678, column: 18)
!1289 = !DILocation(line: 679, column: 19, scope: !1288)
!1290 = !DILocation(line: 679, column: 10, scope: !1288)
!1291 = !DILocation(line: 679, column: 4, scope: !1288)
!1292 = !DILocation(line: 679, column: 8, scope: !1288)
!1293 = !DILocation(line: 680, column: 5, scope: !1288)
!1294 = !DILocation(line: 678, column: 2, scope: !1295)
!1295 = !DILexicalBlockFile(scope: !214, file: !1, discriminator: 2)
!1296 = !DILocation(line: 682, column: 3, scope: !214)
!1297 = !DILocation(line: 682, column: 5, scope: !214)
!1298 = !DILocation(line: 683, column: 2, scope: !214)
