; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_gnutar.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.gnutar = type { i64, i64, i8*, i64, i8*, i64, i8*, i64, i8*, i64, %struct.archive_string_conv*, %struct.archive_string_conv*, i32 }

@.str = private unnamed_addr constant [27 x i8] c"Can't allocate gnutar data\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"gnutar\00", align 1
@.str.2 = private unnamed_addr constant [8 x i8] c"GNU tar\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.4 = private unnamed_addr constant [49 x i8] c"%s: hdrcharset option needs a character-set name\00", align 1
@.str.5 = private unnamed_addr constant [26 x i8] c"Can't allocate ustar data\00", align 1
@.str.6 = private unnamed_addr constant [34 x i8] c"Can't allocate memory for Pathame\00", align 1
@.str.7 = private unnamed_addr constant [36 x i8] c"Can't translate pathname '%s' to %s\00", align 1
@.str.8 = private unnamed_addr constant [32 x i8] c"Can't allocate memory for Uname\00", align 1
@.str.9 = private unnamed_addr constant [33 x i8] c"Can't translate uname '%s' to %s\00", align 1
@.str.10 = private unnamed_addr constant [32 x i8] c"Can't allocate memory for Gname\00", align 1
@.str.11 = private unnamed_addr constant [33 x i8] c"Can't translate gname '%s' to %s\00", align 1
@.str.12 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Linkname\00", align 1
@.str.13 = private unnamed_addr constant [36 x i8] c"Can't translate linkname '%s' to %s\00", align 1
@.str.14 = private unnamed_addr constant [5 x i8] c"root\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"wheel\00", align 1
@.str.16 = private unnamed_addr constant [14 x i8] c"././@LongLink\00", align 1
@.str.17 = private unnamed_addr constant [33 x i8] c"tar format cannot archive socket\00", align 1
@.str.18 = private unnamed_addr constant [43 x i8] c"tar format cannot archive this (mode=0%lo)\00", align 1
@template_header = internal constant [512 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\000000000\000000000\000000000\0000000000000\0000000000000\00        0\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00ustar  \00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 16
@.str.19 = private unnamed_addr constant [30 x i8] c"Numeric user ID %jd too large\00", align 1
@.str.20 = private unnamed_addr constant [31 x i8] c"Numeric group ID %jd too large\00", align 1
@.str.21 = private unnamed_addr constant [23 x i8] c"File size out of range\00", align 1
@.str.22 = private unnamed_addr constant [30 x i8] c"Major device number too large\00", align 1
@.str.23 = private unnamed_addr constant [30 x i8] c"Minor device number too large\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_gnutar(%struct.archive* %_a) #0 !dbg !214 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %gnutar = alloca %struct.gnutar*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !239, metadata !240), !dbg !241
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !242, metadata !240), !dbg !243
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !244
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !245
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !243
  call void @llvm.dbg.declare(metadata %struct.gnutar** %gnutar, metadata !246, metadata !240), !dbg !247
  %call = call noalias i8* @calloc(i64 1, i64 104) #7, !dbg !248
  %2 = bitcast i8* %call to %struct.gnutar*, !dbg !249
  store %struct.gnutar* %2, %struct.gnutar** %gnutar, align 8, !dbg !250
  %3 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !251
  %cmp = icmp eq %struct.gnutar* %3, null, !dbg !253
  br i1 %cmp, label %if.then, label %if.end, !dbg !254

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !255
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !257
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str, i32 0, i32 0)), !dbg !258
  store i32 -30, i32* %retval, align 4, !dbg !259
  br label %return, !dbg !259

if.end:                                           ; preds = %entry
  %5 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !260
  %6 = bitcast %struct.gnutar* %5 to i8*, !dbg !260
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !261
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 14, !dbg !262
  store i8* %6, i8** %format_data, align 8, !dbg !263
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !264
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 15, !dbg !265
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i8** %format_name, align 8, !dbg !266
  %9 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !267
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 17, !dbg !268
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_gnutar_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !269
  %10 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !270
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 19, !dbg !271
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_gnutar_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !272
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !273
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 20, !dbg !274
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_gnutar_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !275
  %12 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !276
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 21, !dbg !277
  store i32 (%struct.archive_write*)* @archive_write_gnutar_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !278
  %13 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !279
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 22, !dbg !280
  store i32 (%struct.archive_write*)* @archive_write_gnutar_free, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !281
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !282
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 18, !dbg !283
  store i32 (%struct.archive_write*)* @archive_write_gnutar_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !284
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !285
  %archive1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 0, !dbg !286
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 3, !dbg !287
  store i32 196612, i32* %archive_format, align 8, !dbg !288
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !289
  %archive2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 0, !dbg !290
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !291
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !292
  store i32 0, i32* %retval, align 4, !dbg !293
  br label %return, !dbg !293

return:                                           ; preds = %if.end, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !294
  ret i32 %17, !dbg !294
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_gnutar_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !215 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %gnutar = alloca %struct.gnutar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !295, metadata !240), !dbg !296
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !297, metadata !240), !dbg !298
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !299, metadata !240), !dbg !300
  call void @llvm.dbg.declare(metadata %struct.gnutar** %gnutar, metadata !301, metadata !240), !dbg !302
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !303
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !304
  %1 = load i8*, i8** %format_data, align 8, !dbg !304
  %2 = bitcast i8* %1 to %struct.gnutar*, !dbg !305
  store %struct.gnutar* %2, %struct.gnutar** %gnutar, align 8, !dbg !302
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !306, metadata !240), !dbg !307
  store i32 -25, i32* %ret, align 4, !dbg !307
  %3 = load i8*, i8** %key.addr, align 8, !dbg !308
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0)) #8, !dbg !310
  %cmp = icmp eq i32 %call, 0, !dbg !311
  br i1 %cmp, label %if.then, label %if.end13, !dbg !312

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !313
  %cmp1 = icmp eq i8* %4, null, !dbg !316
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !317

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !318
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !318
  %6 = load i8, i8* %arrayidx, align 1, !dbg !318
  %conv = sext i8 %6 to i32, !dbg !318
  %cmp2 = icmp eq i32 %conv, 0, !dbg !320
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !321

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !322
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !323
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !324
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 15, !dbg !325
  %9 = load i8*, i8** %format_name, align 8, !dbg !325
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.4, i32 0, i32 0), i8* %9), !dbg !326
  br label %if.end12, !dbg !326

if.else:                                          ; preds = %lor.lhs.false
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !327
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !329
  %11 = load i8*, i8** %val.addr, align 8, !dbg !330
  %call6 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive5, i8* %11, i32 0), !dbg !331
  %12 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !332
  %opt_sconv = getelementptr inbounds %struct.gnutar, %struct.gnutar* %12, i32 0, i32 10, !dbg !333
  store %struct.archive_string_conv* %call6, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !334
  %13 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !335
  %opt_sconv7 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %13, i32 0, i32 10, !dbg !337
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv7, align 8, !dbg !337
  %cmp8 = icmp ne %struct.archive_string_conv* %14, null, !dbg !338
  br i1 %cmp8, label %if.then10, label %if.else11, !dbg !339

if.then10:                                        ; preds = %if.else
  store i32 0, i32* %ret, align 4, !dbg !340
  br label %if.end, !dbg !341

if.else11:                                        ; preds = %if.else
  store i32 -30, i32* %ret, align 4, !dbg !342
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then10
  br label %if.end12

if.end12:                                         ; preds = %if.end, %if.then4
  %15 = load i32, i32* %ret, align 4, !dbg !343
  store i32 %15, i32* %retval, align 4, !dbg !344
  br label %return, !dbg !344

if.end13:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !345
  br label %return, !dbg !345

return:                                           ; preds = %if.end13, %if.end12
  %16 = load i32, i32* %retval, align 4, !dbg !346
  ret i32 %16, !dbg !346
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_gnutar_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !220 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %buff = alloca [512 x i8], align 16
  %r = alloca i32, align 4
  %ret = alloca i32, align 4
  %ret2 = alloca i32, align 4
  %tartype = alloca i32, align 4
  %gnutar = alloca %struct.gnutar*, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  %entry_main = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  %path_length = alloca i64, align 8
  %as = alloca %struct.archive_string, align 8
  %length119 = alloca i64, align 8
  %temp = alloca %struct.archive_entry*, align 8
  %pathname152 = alloca i8*, align 8
  %length154 = alloca i64, align 8
  %temp157 = alloca %struct.archive_entry*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !347, metadata !240), !dbg !348
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !349, metadata !240), !dbg !350
  call void @llvm.dbg.declare(metadata [512 x i8]* %buff, metadata !351, metadata !240), !dbg !353
  call void @llvm.dbg.declare(metadata i32* %r, metadata !354, metadata !240), !dbg !355
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !356, metadata !240), !dbg !357
  call void @llvm.dbg.declare(metadata i32* %ret2, metadata !358, metadata !240), !dbg !359
  store i32 0, i32* %ret2, align 4, !dbg !359
  call void @llvm.dbg.declare(metadata i32* %tartype, metadata !360, metadata !240), !dbg !361
  call void @llvm.dbg.declare(metadata %struct.gnutar** %gnutar, metadata !362, metadata !240), !dbg !363
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !364, metadata !240), !dbg !365
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry_main, metadata !366, metadata !240), !dbg !367
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !368
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !369
  %1 = load i8*, i8** %format_data, align 8, !dbg !369
  %2 = bitcast i8* %1 to %struct.gnutar*, !dbg !370
  store %struct.gnutar* %2, %struct.gnutar** %gnutar, align 8, !dbg !371
  %3 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !372
  %opt_sconv = getelementptr inbounds %struct.gnutar, %struct.gnutar* %3, i32 0, i32 10, !dbg !374
  %4 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !374
  %cmp = icmp eq %struct.archive_string_conv* %4, null, !dbg !375
  br i1 %cmp, label %if.then, label %if.else, !dbg !376

if.then:                                          ; preds = %entry
  %5 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !377
  %init_default_conversion = getelementptr inbounds %struct.gnutar, %struct.gnutar* %5, i32 0, i32 12, !dbg !380
  %6 = load i32, i32* %init_default_conversion, align 8, !dbg !380
  %tobool = icmp ne i32 %6, 0, !dbg !377
  br i1 %tobool, label %if.end, label %if.then2, !dbg !381

if.then2:                                         ; preds = %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !382
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !384
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive* %archive), !dbg !385
  %8 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !386
  %sconv_default = getelementptr inbounds %struct.gnutar, %struct.gnutar* %8, i32 0, i32 11, !dbg !387
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !388
  %9 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !389
  %init_default_conversion3 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %9, i32 0, i32 12, !dbg !390
  store i32 1, i32* %init_default_conversion3, align 8, !dbg !391
  br label %if.end, !dbg !392

if.end:                                           ; preds = %if.then2, %if.then
  %10 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !393
  %sconv_default4 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %10, i32 0, i32 11, !dbg !394
  %11 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default4, align 8, !dbg !394
  store %struct.archive_string_conv* %11, %struct.archive_string_conv** %sconv, align 8, !dbg !395
  br label %if.end6, !dbg !396

if.else:                                          ; preds = %entry
  %12 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !397
  %opt_sconv5 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %12, i32 0, i32 10, !dbg !398
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv5, align 8, !dbg !398
  store %struct.archive_string_conv* %13, %struct.archive_string_conv** %sconv, align 8, !dbg !399
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.end
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !400
  %call7 = call i8* @archive_entry_hardlink(%struct.archive_entry* %14), !dbg !402
  %cmp8 = icmp ne i8* %call7, null, !dbg !403
  br i1 %cmp8, label %if.then14, label %lor.lhs.false, !dbg !404

lor.lhs.false:                                    ; preds = %if.end6
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !405
  %call9 = call i8* @archive_entry_symlink(%struct.archive_entry* %15), !dbg !406
  %cmp10 = icmp ne i8* %call9, null, !dbg !407
  br i1 %cmp10, label %if.then14, label %lor.lhs.false11, !dbg !408

lor.lhs.false11:                                  ; preds = %lor.lhs.false
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !409
  %call12 = call i32 @archive_entry_filetype(%struct.archive_entry* %16), !dbg !410
  %cmp13 = icmp eq i32 %call12, 32768, !dbg !411
  br i1 %cmp13, label %if.end15, label %if.then14, !dbg !412

if.then14:                                        ; preds = %lor.lhs.false11, %lor.lhs.false, %if.end6
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !414
  call void @archive_entry_set_size(%struct.archive_entry* %17, i64 0), !dbg !415
  br label %if.end15, !dbg !415

if.end15:                                         ; preds = %if.then14, %lor.lhs.false11
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !416
  %call16 = call i32 @archive_entry_filetype(%struct.archive_entry* %18), !dbg !418
  %cmp17 = icmp eq i32 16384, %call16, !dbg !419
  br i1 %cmp17, label %if.then18, label %if.end37, !dbg !420

if.then18:                                        ; preds = %if.end15
  call void @llvm.dbg.declare(metadata i8** %p, metadata !421, metadata !240), !dbg !423
  call void @llvm.dbg.declare(metadata i64* %path_length, metadata !424, metadata !240), !dbg !425
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !426
  %call19 = call i8* @archive_entry_pathname(%struct.archive_entry* %19), !dbg !427
  store i8* %call19, i8** %p, align 8, !dbg !428
  %20 = load i8*, i8** %p, align 8, !dbg !429
  %cmp20 = icmp ne i8* %20, null, !dbg !431
  br i1 %cmp20, label %land.lhs.true, label %if.end36, !dbg !432

land.lhs.true:                                    ; preds = %if.then18
  %21 = load i8*, i8** %p, align 8, !dbg !433
  %call21 = call i64 @strlen(i8* %21) #8, !dbg !435
  %sub = sub i64 %call21, 1, !dbg !436
  %22 = load i8*, i8** %p, align 8, !dbg !437
  %arrayidx = getelementptr inbounds i8, i8* %22, i64 %sub, !dbg !437
  %23 = load i8, i8* %arrayidx, align 1, !dbg !437
  %conv = sext i8 %23 to i32, !dbg !437
  %cmp22 = icmp ne i32 %conv, 47, !dbg !438
  br i1 %cmp22, label %if.then24, label %if.end36, !dbg !439

if.then24:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !440, metadata !240), !dbg !442
  br label %do.body, !dbg !443

do.body:                                          ; preds = %if.then24
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !444
  store i8* null, i8** %s, align 8, !dbg !444
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !444
  store i64 0, i64* %length, align 8, !dbg !444
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !444
  store i64 0, i64* %buffer_length, align 8, !dbg !444
  br label %do.end, !dbg !444

do.end:                                           ; preds = %do.body
  %24 = load i8*, i8** %p, align 8, !dbg !447
  %call25 = call i64 @strlen(i8* %24) #8, !dbg !448
  store i64 %call25, i64* %path_length, align 8, !dbg !449
  %25 = load i64, i64* %path_length, align 8, !dbg !450
  %add = add i64 %25, 2, !dbg !452
  %call26 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %as, i64 %add), !dbg !453
  %cmp27 = icmp eq %struct.archive_string* %call26, null, !dbg !454
  br i1 %cmp27, label %if.then29, label %if.end31, !dbg !455

if.then29:                                        ; preds = %do.end
  %26 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !456
  %archive30 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 0, !dbg !458
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive30, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.5, i32 0, i32 0)), !dbg !459
  call void @archive_string_free(%struct.archive_string* %as), !dbg !460
  store i32 -30, i32* %retval, align 4, !dbg !461
  br label %return, !dbg !461

if.end31:                                         ; preds = %do.end
  %length32 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !462
  store i64 0, i64* %length32, align 8, !dbg !462
  %27 = load i8*, i8** %p, align 8, !dbg !462
  %28 = load i64, i64* %path_length, align 8, !dbg !462
  %call33 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %27, i64 %28), !dbg !462
  %call34 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext 47), !dbg !463
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !464
  %s35 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !465
  %30 = load i8*, i8** %s35, align 8, !dbg !465
  call void @archive_entry_copy_pathname(%struct.archive_entry* %29, i8* %30), !dbg !466
  call void @archive_string_free(%struct.archive_string* %as), !dbg !467
  br label %if.end36, !dbg !468

if.end36:                                         ; preds = %if.end31, %land.lhs.true, %if.then18
  br label %if.end37, !dbg !469

if.end37:                                         ; preds = %if.end36, %if.end15
  store %struct.archive_entry* null, %struct.archive_entry** %entry_main, align 8, !dbg !470
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !471
  %32 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !472
  %pathname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %32, i32 0, i32 4, !dbg !473
  %33 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !474
  %pathname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %33, i32 0, i32 5, !dbg !475
  %34 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !476
  %call38 = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %31, i8** %pathname, i64* %pathname_length, %struct.archive_string_conv* %34), !dbg !477
  store i32 %call38, i32* %r, align 4, !dbg !478
  %35 = load i32, i32* %r, align 4, !dbg !479
  %cmp39 = icmp ne i32 %35, 0, !dbg !481
  br i1 %cmp39, label %if.then41, label %if.end51, !dbg !482

if.then41:                                        ; preds = %if.end37
  %call42 = call i32* @__errno_location() #1, !dbg !483
  %36 = load i32, i32* %call42, align 4, !dbg !483
  %cmp43 = icmp eq i32 %36, 12, !dbg !486
  br i1 %cmp43, label %if.then45, label %if.end47, !dbg !487

if.then45:                                        ; preds = %if.then41
  %37 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !488
  %archive46 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %37, i32 0, i32 0, !dbg !490
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive46, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.6, i32 0, i32 0)), !dbg !491
  store i32 -30, i32* %ret, align 4, !dbg !492
  br label %exit_write_header, !dbg !493

if.end47:                                         ; preds = %if.then41
  %38 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !494
  %archive48 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %38, i32 0, i32 0, !dbg !495
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !496
  %call49 = call i8* @archive_entry_pathname(%struct.archive_entry* %39), !dbg !497
  %40 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !498
  %call50 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %40), !dbg !499
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive48, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.7, i32 0, i32 0), i8* %call49, i8* %call50), !dbg !500
  store i32 -20, i32* %ret2, align 4, !dbg !501
  br label %if.end51, !dbg !502

if.end51:                                         ; preds = %if.end47, %if.end37
  %41 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !503
  %42 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !504
  %uname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %42, i32 0, i32 6, !dbg !505
  %43 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !506
  %uname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %43, i32 0, i32 7, !dbg !507
  %44 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !508
  %call52 = call i32 @_archive_entry_uname_l(%struct.archive_entry* %41, i8** %uname, i64* %uname_length, %struct.archive_string_conv* %44), !dbg !509
  store i32 %call52, i32* %r, align 4, !dbg !510
  %45 = load i32, i32* %r, align 4, !dbg !511
  %cmp53 = icmp ne i32 %45, 0, !dbg !513
  br i1 %cmp53, label %if.then55, label %if.end65, !dbg !514

if.then55:                                        ; preds = %if.end51
  %call56 = call i32* @__errno_location() #1, !dbg !515
  %46 = load i32, i32* %call56, align 4, !dbg !515
  %cmp57 = icmp eq i32 %46, 12, !dbg !518
  br i1 %cmp57, label %if.then59, label %if.end61, !dbg !519

if.then59:                                        ; preds = %if.then55
  %47 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !520
  %archive60 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %47, i32 0, i32 0, !dbg !522
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive60, i32 12, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.8, i32 0, i32 0)), !dbg !523
  store i32 -30, i32* %ret, align 4, !dbg !524
  br label %exit_write_header, !dbg !525

if.end61:                                         ; preds = %if.then55
  %48 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !526
  %archive62 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %48, i32 0, i32 0, !dbg !527
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !528
  %call63 = call i8* @archive_entry_uname(%struct.archive_entry* %49), !dbg !529
  %50 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !530
  %call64 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %50), !dbg !531
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive62, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.9, i32 0, i32 0), i8* %call63, i8* %call64), !dbg !532
  store i32 -20, i32* %ret2, align 4, !dbg !533
  br label %if.end65, !dbg !534

if.end65:                                         ; preds = %if.end61, %if.end51
  %51 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !535
  %52 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !536
  %gname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %52, i32 0, i32 8, !dbg !537
  %53 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !538
  %gname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %53, i32 0, i32 9, !dbg !539
  %54 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !540
  %call66 = call i32 @_archive_entry_gname_l(%struct.archive_entry* %51, i8** %gname, i64* %gname_length, %struct.archive_string_conv* %54), !dbg !541
  store i32 %call66, i32* %r, align 4, !dbg !542
  %55 = load i32, i32* %r, align 4, !dbg !543
  %cmp67 = icmp ne i32 %55, 0, !dbg !545
  br i1 %cmp67, label %if.then69, label %if.end79, !dbg !546

if.then69:                                        ; preds = %if.end65
  %call70 = call i32* @__errno_location() #1, !dbg !547
  %56 = load i32, i32* %call70, align 4, !dbg !547
  %cmp71 = icmp eq i32 %56, 12, !dbg !550
  br i1 %cmp71, label %if.then73, label %if.end75, !dbg !551

if.then73:                                        ; preds = %if.then69
  %57 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !552
  %archive74 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %57, i32 0, i32 0, !dbg !554
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive74, i32 12, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.10, i32 0, i32 0)), !dbg !555
  store i32 -30, i32* %ret, align 4, !dbg !556
  br label %exit_write_header, !dbg !557

if.end75:                                         ; preds = %if.then69
  %58 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !558
  %archive76 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %58, i32 0, i32 0, !dbg !559
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !560
  %call77 = call i8* @archive_entry_gname(%struct.archive_entry* %59), !dbg !561
  %60 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !562
  %call78 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %60), !dbg !563
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive76, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.11, i32 0, i32 0), i8* %call77, i8* %call78), !dbg !564
  store i32 -20, i32* %ret2, align 4, !dbg !565
  br label %if.end79, !dbg !566

if.end79:                                         ; preds = %if.end75, %if.end65
  %61 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !567
  %62 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !568
  %linkname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %62, i32 0, i32 2, !dbg !569
  %63 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !570
  %linkname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %63, i32 0, i32 3, !dbg !571
  %64 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !572
  %call80 = call i32 @_archive_entry_hardlink_l(%struct.archive_entry* %61, i8** %linkname, i64* %linkname_length, %struct.archive_string_conv* %64), !dbg !573
  store i32 %call80, i32* %r, align 4, !dbg !574
  %65 = load i32, i32* %r, align 4, !dbg !575
  %cmp81 = icmp ne i32 %65, 0, !dbg !577
  br i1 %cmp81, label %if.then83, label %if.end93, !dbg !578

if.then83:                                        ; preds = %if.end79
  %call84 = call i32* @__errno_location() #1, !dbg !579
  %66 = load i32, i32* %call84, align 4, !dbg !579
  %cmp85 = icmp eq i32 %66, 12, !dbg !582
  br i1 %cmp85, label %if.then87, label %if.end89, !dbg !583

if.then87:                                        ; preds = %if.then83
  %67 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !584
  %archive88 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %67, i32 0, i32 0, !dbg !586
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive88, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.12, i32 0, i32 0)), !dbg !587
  store i32 -30, i32* %ret, align 4, !dbg !588
  br label %exit_write_header, !dbg !589

if.end89:                                         ; preds = %if.then83
  %68 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !590
  %archive90 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %68, i32 0, i32 0, !dbg !591
  %69 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !592
  %call91 = call i8* @archive_entry_hardlink(%struct.archive_entry* %69), !dbg !593
  %70 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !594
  %call92 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %70), !dbg !595
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive90, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.13, i32 0, i32 0), i8* %call91, i8* %call92), !dbg !596
  store i32 -20, i32* %ret2, align 4, !dbg !597
  br label %if.end93, !dbg !598

if.end93:                                         ; preds = %if.end89, %if.end79
  %71 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !599
  %linkname_length94 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %71, i32 0, i32 3, !dbg !601
  %72 = load i64, i64* %linkname_length94, align 8, !dbg !601
  %cmp95 = icmp eq i64 %72, 0, !dbg !602
  br i1 %cmp95, label %if.then97, label %if.end114, !dbg !603

if.then97:                                        ; preds = %if.end93
  %73 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !604
  %74 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !606
  %linkname98 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %74, i32 0, i32 2, !dbg !607
  %75 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !608
  %linkname_length99 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %75, i32 0, i32 3, !dbg !609
  %76 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !610
  %call100 = call i32 @_archive_entry_symlink_l(%struct.archive_entry* %73, i8** %linkname98, i64* %linkname_length99, %struct.archive_string_conv* %76), !dbg !611
  store i32 %call100, i32* %r, align 4, !dbg !612
  %77 = load i32, i32* %r, align 4, !dbg !613
  %cmp101 = icmp ne i32 %77, 0, !dbg !615
  br i1 %cmp101, label %if.then103, label %if.end113, !dbg !616

if.then103:                                       ; preds = %if.then97
  %call104 = call i32* @__errno_location() #1, !dbg !617
  %78 = load i32, i32* %call104, align 4, !dbg !617
  %cmp105 = icmp eq i32 %78, 12, !dbg !620
  br i1 %cmp105, label %if.then107, label %if.end109, !dbg !621

if.then107:                                       ; preds = %if.then103
  %79 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !622
  %archive108 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %79, i32 0, i32 0, !dbg !624
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive108, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.12, i32 0, i32 0)), !dbg !625
  store i32 -30, i32* %ret, align 4, !dbg !626
  br label %exit_write_header, !dbg !627

if.end109:                                        ; preds = %if.then103
  %80 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !628
  %archive110 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %80, i32 0, i32 0, !dbg !629
  %81 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !630
  %call111 = call i8* @archive_entry_hardlink(%struct.archive_entry* %81), !dbg !631
  %82 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !632
  %call112 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %82), !dbg !633
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive110, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.13, i32 0, i32 0), i8* %call111, i8* %call112), !dbg !634
  store i32 -20, i32* %ret2, align 4, !dbg !635
  br label %if.end113, !dbg !636

if.end113:                                        ; preds = %if.end109, %if.then97
  br label %if.end114, !dbg !637

if.end114:                                        ; preds = %if.end113, %if.end93
  %83 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !638
  %linkname_length115 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %83, i32 0, i32 3, !dbg !640
  %84 = load i64, i64* %linkname_length115, align 8, !dbg !640
  %cmp116 = icmp ugt i64 %84, 100, !dbg !641
  br i1 %cmp116, label %if.then118, label %if.end147, !dbg !642

if.then118:                                       ; preds = %if.end114
  call void @llvm.dbg.declare(metadata i64* %length119, metadata !643, metadata !240), !dbg !645
  %85 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !646
  %linkname_length120 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %85, i32 0, i32 3, !dbg !647
  %86 = load i64, i64* %linkname_length120, align 8, !dbg !647
  %add121 = add i64 %86, 1, !dbg !648
  store i64 %add121, i64* %length119, align 8, !dbg !645
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %temp, metadata !649, metadata !240), !dbg !650
  %87 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !651
  %archive122 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %87, i32 0, i32 0, !dbg !652
  %call123 = call %struct.archive_entry* @archive_entry_new2(%struct.archive* %archive122), !dbg !653
  store %struct.archive_entry* %call123, %struct.archive_entry** %temp, align 8, !dbg !650
  %88 = load %struct.archive_entry*, %struct.archive_entry** %temp, align 8, !dbg !654
  call void @archive_entry_set_uname(%struct.archive_entry* %88, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.14, i32 0, i32 0)), !dbg !655
  %89 = load %struct.archive_entry*, %struct.archive_entry** %temp, align 8, !dbg !656
  call void @archive_entry_set_gname(%struct.archive_entry* %89, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i32 0, i32 0)), !dbg !657
  %90 = load %struct.archive_entry*, %struct.archive_entry** %temp, align 8, !dbg !658
  call void @archive_entry_set_pathname(%struct.archive_entry* %90, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.16, i32 0, i32 0)), !dbg !659
  %91 = load %struct.archive_entry*, %struct.archive_entry** %temp, align 8, !dbg !660
  %92 = load i64, i64* %length119, align 8, !dbg !661
  call void @archive_entry_set_size(%struct.archive_entry* %91, i64 %92), !dbg !662
  %93 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !663
  %arraydecay = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !664
  %94 = load %struct.archive_entry*, %struct.archive_entry** %temp, align 8, !dbg !665
  %call124 = call i32 @archive_format_gnutar_header(%struct.archive_write* %93, i8* %arraydecay, %struct.archive_entry* %94, i32 75), !dbg !666
  store i32 %call124, i32* %ret, align 4, !dbg !667
  %95 = load %struct.archive_entry*, %struct.archive_entry** %temp, align 8, !dbg !668
  call void @archive_entry_free(%struct.archive_entry* %95), !dbg !669
  %96 = load i32, i32* %ret, align 4, !dbg !670
  %cmp125 = icmp slt i32 %96, -20, !dbg !672
  br i1 %cmp125, label %if.then127, label %if.end128, !dbg !673

if.then127:                                       ; preds = %if.then118
  br label %exit_write_header, !dbg !674

if.end128:                                        ; preds = %if.then118
  %97 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !675
  %arraydecay129 = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !676
  %call130 = call i32 @__archive_write_output(%struct.archive_write* %97, i8* %arraydecay129, i64 512), !dbg !677
  store i32 %call130, i32* %ret, align 4, !dbg !678
  %98 = load i32, i32* %ret, align 4, !dbg !679
  %cmp131 = icmp slt i32 %98, -20, !dbg !681
  br i1 %cmp131, label %if.then133, label %if.end134, !dbg !682

if.then133:                                       ; preds = %if.end128
  br label %exit_write_header, !dbg !683

if.end134:                                        ; preds = %if.end128
  %99 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !684
  %100 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !685
  %linkname135 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %100, i32 0, i32 2, !dbg !686
  %101 = load i8*, i8** %linkname135, align 8, !dbg !686
  %102 = load i64, i64* %length119, align 8, !dbg !687
  %call136 = call i32 @__archive_write_output(%struct.archive_write* %99, i8* %101, i64 %102), !dbg !688
  store i32 %call136, i32* %ret, align 4, !dbg !689
  %103 = load i32, i32* %ret, align 4, !dbg !690
  %cmp137 = icmp slt i32 %103, -20, !dbg !692
  br i1 %cmp137, label %if.then139, label %if.end140, !dbg !693

if.then139:                                       ; preds = %if.end134
  br label %exit_write_header, !dbg !694

if.end140:                                        ; preds = %if.end134
  %104 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !695
  %105 = load i64, i64* %length119, align 8, !dbg !696
  %sub141 = sub nsw i64 0, %105, !dbg !697
  %and = and i64 511, %sub141, !dbg !698
  %call142 = call i32 @__archive_write_nulls(%struct.archive_write* %104, i64 %and), !dbg !699
  store i32 %call142, i32* %ret, align 4, !dbg !700
  %106 = load i32, i32* %ret, align 4, !dbg !701
  %cmp143 = icmp slt i32 %106, -20, !dbg !703
  br i1 %cmp143, label %if.then145, label %if.end146, !dbg !704

if.then145:                                       ; preds = %if.end140
  br label %exit_write_header, !dbg !705

if.end146:                                        ; preds = %if.end140
  br label %if.end147, !dbg !706

if.end147:                                        ; preds = %if.end146, %if.end114
  %107 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !707
  %pathname_length148 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %107, i32 0, i32 5, !dbg !709
  %108 = load i64, i64* %pathname_length148, align 8, !dbg !709
  %cmp149 = icmp ugt i64 %108, 100, !dbg !710
  br i1 %cmp149, label %if.then151, label %if.end184, !dbg !711

if.then151:                                       ; preds = %if.end147
  call void @llvm.dbg.declare(metadata i8** %pathname152, metadata !712, metadata !240), !dbg !714
  %109 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !715
  %pathname153 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %109, i32 0, i32 4, !dbg !716
  %110 = load i8*, i8** %pathname153, align 8, !dbg !716
  store i8* %110, i8** %pathname152, align 8, !dbg !714
  call void @llvm.dbg.declare(metadata i64* %length154, metadata !717, metadata !240), !dbg !718
  %111 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !719
  %pathname_length155 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %111, i32 0, i32 5, !dbg !720
  %112 = load i64, i64* %pathname_length155, align 8, !dbg !720
  %add156 = add i64 %112, 1, !dbg !721
  store i64 %add156, i64* %length154, align 8, !dbg !718
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %temp157, metadata !722, metadata !240), !dbg !723
  %113 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !724
  %archive158 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %113, i32 0, i32 0, !dbg !725
  %call159 = call %struct.archive_entry* @archive_entry_new2(%struct.archive* %archive158), !dbg !726
  store %struct.archive_entry* %call159, %struct.archive_entry** %temp157, align 8, !dbg !723
  %114 = load %struct.archive_entry*, %struct.archive_entry** %temp157, align 8, !dbg !727
  call void @archive_entry_set_uname(%struct.archive_entry* %114, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.14, i32 0, i32 0)), !dbg !728
  %115 = load %struct.archive_entry*, %struct.archive_entry** %temp157, align 8, !dbg !729
  call void @archive_entry_set_gname(%struct.archive_entry* %115, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i32 0, i32 0)), !dbg !730
  %116 = load %struct.archive_entry*, %struct.archive_entry** %temp157, align 8, !dbg !731
  call void @archive_entry_set_pathname(%struct.archive_entry* %116, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.16, i32 0, i32 0)), !dbg !732
  %117 = load %struct.archive_entry*, %struct.archive_entry** %temp157, align 8, !dbg !733
  %118 = load i64, i64* %length154, align 8, !dbg !734
  call void @archive_entry_set_size(%struct.archive_entry* %117, i64 %118), !dbg !735
  %119 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !736
  %arraydecay160 = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !737
  %120 = load %struct.archive_entry*, %struct.archive_entry** %temp157, align 8, !dbg !738
  %call161 = call i32 @archive_format_gnutar_header(%struct.archive_write* %119, i8* %arraydecay160, %struct.archive_entry* %120, i32 76), !dbg !739
  store i32 %call161, i32* %ret, align 4, !dbg !740
  %121 = load %struct.archive_entry*, %struct.archive_entry** %temp157, align 8, !dbg !741
  call void @archive_entry_free(%struct.archive_entry* %121), !dbg !742
  %122 = load i32, i32* %ret, align 4, !dbg !743
  %cmp162 = icmp slt i32 %122, -20, !dbg !745
  br i1 %cmp162, label %if.then164, label %if.end165, !dbg !746

if.then164:                                       ; preds = %if.then151
  br label %exit_write_header, !dbg !747

if.end165:                                        ; preds = %if.then151
  %123 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !748
  %arraydecay166 = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !749
  %call167 = call i32 @__archive_write_output(%struct.archive_write* %123, i8* %arraydecay166, i64 512), !dbg !750
  store i32 %call167, i32* %ret, align 4, !dbg !751
  %124 = load i32, i32* %ret, align 4, !dbg !752
  %cmp168 = icmp slt i32 %124, -20, !dbg !754
  br i1 %cmp168, label %if.then170, label %if.end171, !dbg !755

if.then170:                                       ; preds = %if.end165
  br label %exit_write_header, !dbg !756

if.end171:                                        ; preds = %if.end165
  %125 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !757
  %126 = load i8*, i8** %pathname152, align 8, !dbg !758
  %127 = load i64, i64* %length154, align 8, !dbg !759
  %call172 = call i32 @__archive_write_output(%struct.archive_write* %125, i8* %126, i64 %127), !dbg !760
  store i32 %call172, i32* %ret, align 4, !dbg !761
  %128 = load i32, i32* %ret, align 4, !dbg !762
  %cmp173 = icmp slt i32 %128, -20, !dbg !764
  br i1 %cmp173, label %if.then175, label %if.end176, !dbg !765

if.then175:                                       ; preds = %if.end171
  br label %exit_write_header, !dbg !766

if.end176:                                        ; preds = %if.end171
  %129 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !767
  %130 = load i64, i64* %length154, align 8, !dbg !768
  %sub177 = sub nsw i64 0, %130, !dbg !769
  %and178 = and i64 511, %sub177, !dbg !770
  %call179 = call i32 @__archive_write_nulls(%struct.archive_write* %129, i64 %and178), !dbg !771
  store i32 %call179, i32* %ret, align 4, !dbg !772
  %131 = load i32, i32* %ret, align 4, !dbg !773
  %cmp180 = icmp slt i32 %131, -20, !dbg !775
  br i1 %cmp180, label %if.then182, label %if.end183, !dbg !776

if.then182:                                       ; preds = %if.end176
  br label %exit_write_header, !dbg !777

if.end183:                                        ; preds = %if.end176
  br label %if.end184, !dbg !778

if.end184:                                        ; preds = %if.end183, %if.end147
  %132 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !779
  %call185 = call i8* @archive_entry_hardlink(%struct.archive_entry* %132), !dbg !781
  %cmp186 = icmp ne i8* %call185, null, !dbg !782
  br i1 %cmp186, label %if.then188, label %if.else189, !dbg !783

if.then188:                                       ; preds = %if.end184
  store i32 49, i32* %tartype, align 4, !dbg !784
  br label %if.end201, !dbg !786

if.else189:                                       ; preds = %if.end184
  %133 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !787
  %call190 = call i32 @archive_entry_filetype(%struct.archive_entry* %133), !dbg !788
  switch i32 %call190, label %sw.default [
    i32 32768, label %sw.bb
    i32 40960, label %sw.bb191
    i32 8192, label %sw.bb192
    i32 24576, label %sw.bb193
    i32 16384, label %sw.bb194
    i32 4096, label %sw.bb195
    i32 49152, label %sw.bb196
  ], !dbg !789

sw.bb:                                            ; preds = %if.else189
  store i32 48, i32* %tartype, align 4, !dbg !790
  br label %sw.epilog, !dbg !792

sw.bb191:                                         ; preds = %if.else189
  store i32 50, i32* %tartype, align 4, !dbg !793
  br label %sw.epilog, !dbg !794

sw.bb192:                                         ; preds = %if.else189
  store i32 51, i32* %tartype, align 4, !dbg !795
  br label %sw.epilog, !dbg !796

sw.bb193:                                         ; preds = %if.else189
  store i32 52, i32* %tartype, align 4, !dbg !797
  br label %sw.epilog, !dbg !798

sw.bb194:                                         ; preds = %if.else189
  store i32 53, i32* %tartype, align 4, !dbg !799
  br label %sw.epilog, !dbg !800

sw.bb195:                                         ; preds = %if.else189
  store i32 54, i32* %tartype, align 4, !dbg !801
  br label %sw.epilog, !dbg !802

sw.bb196:                                         ; preds = %if.else189
  %134 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !803
  %archive197 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %134, i32 0, i32 0, !dbg !804
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive197, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.17, i32 0, i32 0)), !dbg !805
  store i32 -25, i32* %ret, align 4, !dbg !806
  br label %exit_write_header, !dbg !807

sw.default:                                       ; preds = %if.else189
  %135 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !808
  %archive198 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %135, i32 0, i32 0, !dbg !809
  %136 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !810
  %call199 = call i32 @archive_entry_mode(%struct.archive_entry* %136), !dbg !811
  %conv200 = zext i32 %call199 to i64, !dbg !812
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive198, i32 84, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.18, i32 0, i32 0), i64 %conv200), !dbg !813
  store i32 -25, i32* %ret, align 4, !dbg !814
  br label %exit_write_header, !dbg !815

sw.epilog:                                        ; preds = %sw.bb195, %sw.bb194, %sw.bb193, %sw.bb192, %sw.bb191, %sw.bb
  br label %if.end201

if.end201:                                        ; preds = %sw.epilog, %if.then188
  %137 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !816
  %arraydecay202 = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !817
  %138 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !818
  %139 = load i32, i32* %tartype, align 4, !dbg !819
  %call203 = call i32 @archive_format_gnutar_header(%struct.archive_write* %137, i8* %arraydecay202, %struct.archive_entry* %138, i32 %139), !dbg !820
  store i32 %call203, i32* %ret, align 4, !dbg !821
  %140 = load i32, i32* %ret, align 4, !dbg !822
  %cmp204 = icmp slt i32 %140, -20, !dbg !824
  br i1 %cmp204, label %if.then206, label %if.end207, !dbg !825

if.then206:                                       ; preds = %if.end201
  br label %exit_write_header, !dbg !826

if.end207:                                        ; preds = %if.end201
  %141 = load i32, i32* %ret2, align 4, !dbg !827
  %142 = load i32, i32* %ret, align 4, !dbg !829
  %cmp208 = icmp slt i32 %141, %142, !dbg !830
  br i1 %cmp208, label %if.then210, label %if.end211, !dbg !831

if.then210:                                       ; preds = %if.end207
  %143 = load i32, i32* %ret2, align 4, !dbg !832
  store i32 %143, i32* %ret, align 4, !dbg !833
  br label %if.end211, !dbg !834

if.end211:                                        ; preds = %if.then210, %if.end207
  %144 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !835
  %arraydecay212 = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !836
  %call213 = call i32 @__archive_write_output(%struct.archive_write* %144, i8* %arraydecay212, i64 512), !dbg !837
  store i32 %call213, i32* %ret2, align 4, !dbg !838
  %145 = load i32, i32* %ret2, align 4, !dbg !839
  %cmp214 = icmp slt i32 %145, -20, !dbg !841
  br i1 %cmp214, label %if.then216, label %if.end217, !dbg !842

if.then216:                                       ; preds = %if.end211
  %146 = load i32, i32* %ret2, align 4, !dbg !843
  store i32 %146, i32* %ret, align 4, !dbg !845
  br label %exit_write_header, !dbg !846

if.end217:                                        ; preds = %if.end211
  %147 = load i32, i32* %ret2, align 4, !dbg !847
  %148 = load i32, i32* %ret, align 4, !dbg !849
  %cmp218 = icmp slt i32 %147, %148, !dbg !850
  br i1 %cmp218, label %if.then220, label %if.end221, !dbg !851

if.then220:                                       ; preds = %if.end217
  %149 = load i32, i32* %ret2, align 4, !dbg !852
  store i32 %149, i32* %ret, align 4, !dbg !853
  br label %if.end221, !dbg !854

if.end221:                                        ; preds = %if.then220, %if.end217
  %150 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !855
  %call222 = call i64 @archive_entry_size(%struct.archive_entry* %150), !dbg !856
  %151 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !857
  %entry_bytes_remaining = getelementptr inbounds %struct.gnutar, %struct.gnutar* %151, i32 0, i32 0, !dbg !858
  store i64 %call222, i64* %entry_bytes_remaining, align 8, !dbg !859
  %152 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !860
  %entry_bytes_remaining223 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %152, i32 0, i32 0, !dbg !861
  %153 = load i64, i64* %entry_bytes_remaining223, align 8, !dbg !861
  %sub224 = sub nsw i64 0, %153, !dbg !862
  %and225 = and i64 511, %sub224, !dbg !863
  %154 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !864
  %entry_padding = getelementptr inbounds %struct.gnutar, %struct.gnutar* %154, i32 0, i32 1, !dbg !865
  store i64 %and225, i64* %entry_padding, align 8, !dbg !866
  br label %exit_write_header, !dbg !864

exit_write_header:                                ; preds = %if.end221, %if.then216, %if.then206, %sw.default, %sw.bb196, %if.then182, %if.then175, %if.then170, %if.then164, %if.then145, %if.then139, %if.then133, %if.then127, %if.then107, %if.then87, %if.then73, %if.then59, %if.then45
  %155 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !867
  %tobool226 = icmp ne %struct.archive_entry* %155, null, !dbg !867
  br i1 %tobool226, label %if.then227, label %if.end228, !dbg !869

if.then227:                                       ; preds = %exit_write_header
  %156 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !870
  call void @archive_entry_free(%struct.archive_entry* %156), !dbg !871
  br label %if.end228, !dbg !871

if.end228:                                        ; preds = %if.then227, %exit_write_header
  %157 = load i32, i32* %ret, align 4, !dbg !872
  store i32 %157, i32* %retval, align 4, !dbg !873
  br label %return, !dbg !873

return:                                           ; preds = %if.end228, %if.then29
  %158 = load i32, i32* %retval, align 4, !dbg !874
  ret i32 %158, !dbg !874
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_gnutar_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !219 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %gnutar = alloca %struct.gnutar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !875, metadata !240), !dbg !876
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !877, metadata !240), !dbg !878
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !879, metadata !240), !dbg !880
  call void @llvm.dbg.declare(metadata %struct.gnutar** %gnutar, metadata !881, metadata !240), !dbg !882
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !883, metadata !240), !dbg !884
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !885
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !886
  %1 = load i8*, i8** %format_data, align 8, !dbg !886
  %2 = bitcast i8* %1 to %struct.gnutar*, !dbg !887
  store %struct.gnutar* %2, %struct.gnutar** %gnutar, align 8, !dbg !888
  %3 = load i64, i64* %s.addr, align 8, !dbg !889
  %4 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !891
  %entry_bytes_remaining = getelementptr inbounds %struct.gnutar, %struct.gnutar* %4, i32 0, i32 0, !dbg !892
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !892
  %cmp = icmp ugt i64 %3, %5, !dbg !893
  br i1 %cmp, label %if.then, label %if.end, !dbg !894

if.then:                                          ; preds = %entry
  %6 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !895
  %entry_bytes_remaining1 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %6, i32 0, i32 0, !dbg !896
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !896
  store i64 %7, i64* %s.addr, align 8, !dbg !897
  br label %if.end, !dbg !898

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !899
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !900
  %10 = load i64, i64* %s.addr, align 8, !dbg !901
  %call = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %9, i64 %10), !dbg !902
  store i32 %call, i32* %ret, align 4, !dbg !903
  %11 = load i64, i64* %s.addr, align 8, !dbg !904
  %12 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !905
  %entry_bytes_remaining2 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %12, i32 0, i32 0, !dbg !906
  %13 = load i64, i64* %entry_bytes_remaining2, align 8, !dbg !907
  %sub = sub i64 %13, %11, !dbg !907
  store i64 %sub, i64* %entry_bytes_remaining2, align 8, !dbg !907
  %14 = load i32, i32* %ret, align 4, !dbg !908
  %cmp3 = icmp ne i32 %14, 0, !dbg !910
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !911

if.then4:                                         ; preds = %if.end
  %15 = load i32, i32* %ret, align 4, !dbg !912
  %conv = sext i32 %15 to i64, !dbg !913
  store i64 %conv, i64* %retval, align 8, !dbg !914
  br label %return, !dbg !914

if.end5:                                          ; preds = %if.end
  %16 = load i64, i64* %s.addr, align 8, !dbg !915
  store i64 %16, i64* %retval, align 8, !dbg !916
  br label %return, !dbg !916

return:                                           ; preds = %if.end5, %if.then4
  %17 = load i64, i64* %retval, align 8, !dbg !917
  ret i64 %17, !dbg !917
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_gnutar_close(%struct.archive_write* %a) #0 !dbg !216 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !918, metadata !240), !dbg !919
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !920
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %0, i64 1024), !dbg !921
  ret i32 %call, !dbg !922
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_gnutar_free(%struct.archive_write* %a) #0 !dbg !217 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %gnutar = alloca %struct.gnutar*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !923, metadata !240), !dbg !924
  call void @llvm.dbg.declare(metadata %struct.gnutar** %gnutar, metadata !925, metadata !240), !dbg !926
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !927
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !928
  %1 = load i8*, i8** %format_data, align 8, !dbg !928
  %2 = bitcast i8* %1 to %struct.gnutar*, !dbg !929
  store %struct.gnutar* %2, %struct.gnutar** %gnutar, align 8, !dbg !930
  %3 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !931
  %4 = bitcast %struct.gnutar* %3 to i8*, !dbg !931
  call void @free(i8* %4) #7, !dbg !932
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !933
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 14, !dbg !934
  store i8* null, i8** %format_data1, align 8, !dbg !935
  ret i32 0, !dbg !936
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_gnutar_finish_entry(%struct.archive_write* %a) #0 !dbg !218 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %gnutar = alloca %struct.gnutar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !937, metadata !240), !dbg !938
  call void @llvm.dbg.declare(metadata %struct.gnutar** %gnutar, metadata !939, metadata !240), !dbg !940
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !941, metadata !240), !dbg !942
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !943
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !944
  %1 = load i8*, i8** %format_data, align 8, !dbg !944
  %2 = bitcast i8* %1 to %struct.gnutar*, !dbg !945
  store %struct.gnutar* %2, %struct.gnutar** %gnutar, align 8, !dbg !946
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !947
  %4 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !948
  %entry_bytes_remaining = getelementptr inbounds %struct.gnutar, %struct.gnutar* %4, i32 0, i32 0, !dbg !949
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !949
  %6 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !950
  %entry_padding = getelementptr inbounds %struct.gnutar, %struct.gnutar* %6, i32 0, i32 1, !dbg !951
  %7 = load i64, i64* %entry_padding, align 8, !dbg !951
  %add = add i64 %5, %7, !dbg !952
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %3, i64 %add), !dbg !953
  store i32 %call, i32* %ret, align 4, !dbg !954
  %8 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !955
  %entry_padding1 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %8, i32 0, i32 1, !dbg !956
  store i64 0, i64* %entry_padding1, align 8, !dbg !957
  %9 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !958
  %entry_bytes_remaining2 = getelementptr inbounds %struct.gnutar, %struct.gnutar* %9, i32 0, i32 0, !dbg !959
  store i64 0, i64* %entry_bytes_remaining2, align 8, !dbg !960
  %10 = load i32, i32* %ret, align 4, !dbg !961
  ret i32 %10, !dbg !962
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #3

declare i32 @__archive_write_nulls(%struct.archive_write*, i64) #3

; Function Attrs: nounwind
declare void @free(i8*) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #3

declare %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive*) #3

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #3

declare i8* @archive_entry_symlink(%struct.archive_entry*) #3

declare i32 @archive_entry_filetype(%struct.archive_entry*) #3

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #3

declare i8* @archive_entry_pathname(%struct.archive_entry*) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #3

declare void @archive_string_free(%struct.archive_string*) #3

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #3

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #3

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #3

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #3

declare i32 @_archive_entry_uname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #3

declare i8* @archive_entry_uname(%struct.archive_entry*) #3

declare i32 @_archive_entry_gname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #3

declare i8* @archive_entry_gname(%struct.archive_entry*) #3

declare i32 @_archive_entry_hardlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #3

declare i32 @_archive_entry_symlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #3

declare %struct.archive_entry* @archive_entry_new2(%struct.archive*) #3

declare void @archive_entry_set_uname(%struct.archive_entry*, i8*) #3

declare void @archive_entry_set_gname(%struct.archive_entry*, i8*) #3

declare void @archive_entry_set_pathname(%struct.archive_entry*, i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_format_gnutar_header(%struct.archive_write* %a, i8* %h, %struct.archive_entry* %entry1, i32 %tartype) #0 !dbg !221 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %h.addr = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %tartype.addr = alloca i32, align 4
  %checksum = alloca i32, align 4
  %i = alloca i32, align 4
  %ret = alloca i32, align 4
  %copy_length = alloca i64, align 8
  %p = alloca i8*, align 8
  %gnutar = alloca %struct.gnutar*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !963, metadata !240), !dbg !964
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !965, metadata !240), !dbg !966
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !967, metadata !240), !dbg !968
  store i32 %tartype, i32* %tartype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tartype.addr, metadata !969, metadata !240), !dbg !970
  call void @llvm.dbg.declare(metadata i32* %checksum, metadata !971, metadata !240), !dbg !972
  call void @llvm.dbg.declare(metadata i32* %i, metadata !973, metadata !240), !dbg !974
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !975, metadata !240), !dbg !976
  call void @llvm.dbg.declare(metadata i64* %copy_length, metadata !977, metadata !240), !dbg !978
  call void @llvm.dbg.declare(metadata i8** %p, metadata !979, metadata !240), !dbg !980
  call void @llvm.dbg.declare(metadata %struct.gnutar** %gnutar, metadata !981, metadata !240), !dbg !982
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !983
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !984
  %1 = load i8*, i8** %format_data, align 8, !dbg !984
  %2 = bitcast i8* %1 to %struct.gnutar*, !dbg !985
  store %struct.gnutar* %2, %struct.gnutar** %gnutar, align 8, !dbg !986
  store i32 0, i32* %ret, align 4, !dbg !987
  %3 = load i8*, i8** %h.addr, align 8, !dbg !988
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* getelementptr inbounds ([512 x i8], [512 x i8]* @template_header, i32 0, i32 0), i64 512, i32 1, i1 false), !dbg !989
  %4 = load i32, i32* %tartype.addr, align 4, !dbg !990
  %cmp = icmp eq i32 %4, 75, !dbg !992
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !993

lor.lhs.false:                                    ; preds = %entry
  %5 = load i32, i32* %tartype.addr, align 4, !dbg !994
  %cmp2 = icmp eq i32 %5, 76, !dbg !996
  br i1 %cmp2, label %if.then, label %if.else, !dbg !997

if.then:                                          ; preds = %lor.lhs.false, %entry
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !998
  %call = call i8* @archive_entry_pathname(%struct.archive_entry* %6), !dbg !1000
  store i8* %call, i8** %p, align 8, !dbg !1001
  %7 = load i8*, i8** %p, align 8, !dbg !1002
  %call3 = call i64 @strlen(i8* %7) #8, !dbg !1003
  store i64 %call3, i64* %copy_length, align 8, !dbg !1004
  br label %if.end, !dbg !1005

if.else:                                          ; preds = %lor.lhs.false
  %8 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1006
  %pathname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %8, i32 0, i32 4, !dbg !1008
  %9 = load i8*, i8** %pathname, align 8, !dbg !1008
  store i8* %9, i8** %p, align 8, !dbg !1009
  %10 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1010
  %pathname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %10, i32 0, i32 5, !dbg !1011
  %11 = load i64, i64* %pathname_length, align 8, !dbg !1011
  store i64 %11, i64* %copy_length, align 8, !dbg !1012
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %12 = load i64, i64* %copy_length, align 8, !dbg !1013
  %cmp4 = icmp ugt i64 %12, 100, !dbg !1015
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1016

if.then5:                                         ; preds = %if.end
  store i64 100, i64* %copy_length, align 8, !dbg !1017
  br label %if.end6, !dbg !1018

if.end6:                                          ; preds = %if.then5, %if.end
  %13 = load i8*, i8** %h.addr, align 8, !dbg !1019
  %add.ptr = getelementptr inbounds i8, i8* %13, i64 0, !dbg !1020
  %14 = load i8*, i8** %p, align 8, !dbg !1021
  %15 = load i64, i64* %copy_length, align 8, !dbg !1022
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %14, i64 %15, i32 1, i1 false), !dbg !1023
  %16 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1024
  %linkname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %16, i32 0, i32 3, !dbg !1026
  %17 = load i64, i64* %linkname_length, align 8, !dbg !1026
  store i64 %17, i64* %copy_length, align 8, !dbg !1027
  %cmp7 = icmp ugt i64 %17, 0, !dbg !1028
  br i1 %cmp7, label %if.then8, label %if.end13, !dbg !1029

if.then8:                                         ; preds = %if.end6
  %18 = load i64, i64* %copy_length, align 8, !dbg !1030
  %cmp9 = icmp ugt i64 %18, 100, !dbg !1033
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !1034

if.then10:                                        ; preds = %if.then8
  store i64 100, i64* %copy_length, align 8, !dbg !1035
  br label %if.end11, !dbg !1036

if.end11:                                         ; preds = %if.then10, %if.then8
  %19 = load i8*, i8** %h.addr, align 8, !dbg !1037
  %add.ptr12 = getelementptr inbounds i8, i8* %19, i64 157, !dbg !1038
  %20 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1039
  %linkname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %20, i32 0, i32 2, !dbg !1040
  %21 = load i8*, i8** %linkname, align 8, !dbg !1040
  %22 = load i64, i64* %copy_length, align 8, !dbg !1041
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr12, i8* %21, i64 %22, i32 1, i1 false), !dbg !1042
  br label %if.end13, !dbg !1043

if.end13:                                         ; preds = %if.end11, %if.end6
  %23 = load i32, i32* %tartype.addr, align 4, !dbg !1044
  %cmp14 = icmp eq i32 %23, 75, !dbg !1046
  br i1 %cmp14, label %if.then17, label %lor.lhs.false15, !dbg !1047

lor.lhs.false15:                                  ; preds = %if.end13
  %24 = load i32, i32* %tartype.addr, align 4, !dbg !1048
  %cmp16 = icmp eq i32 %24, 76, !dbg !1050
  br i1 %cmp16, label %if.then17, label %if.else20, !dbg !1051

if.then17:                                        ; preds = %lor.lhs.false15, %if.end13
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1052
  %call18 = call i8* @archive_entry_uname(%struct.archive_entry* %25), !dbg !1054
  store i8* %call18, i8** %p, align 8, !dbg !1055
  %26 = load i8*, i8** %p, align 8, !dbg !1056
  %call19 = call i64 @strlen(i8* %26) #8, !dbg !1057
  store i64 %call19, i64* %copy_length, align 8, !dbg !1058
  br label %if.end21, !dbg !1059

if.else20:                                        ; preds = %lor.lhs.false15
  %27 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1060
  %uname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %27, i32 0, i32 6, !dbg !1062
  %28 = load i8*, i8** %uname, align 8, !dbg !1062
  store i8* %28, i8** %p, align 8, !dbg !1063
  %29 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1064
  %uname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %29, i32 0, i32 7, !dbg !1065
  %30 = load i64, i64* %uname_length, align 8, !dbg !1065
  store i64 %30, i64* %copy_length, align 8, !dbg !1066
  br label %if.end21

if.end21:                                         ; preds = %if.else20, %if.then17
  %31 = load i64, i64* %copy_length, align 8, !dbg !1067
  %cmp22 = icmp ugt i64 %31, 0, !dbg !1069
  br i1 %cmp22, label %if.then23, label %if.end28, !dbg !1070

if.then23:                                        ; preds = %if.end21
  %32 = load i64, i64* %copy_length, align 8, !dbg !1071
  %cmp24 = icmp ugt i64 %32, 32, !dbg !1074
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !1075

if.then25:                                        ; preds = %if.then23
  store i64 32, i64* %copy_length, align 8, !dbg !1076
  br label %if.end26, !dbg !1077

if.end26:                                         ; preds = %if.then25, %if.then23
  %33 = load i8*, i8** %h.addr, align 8, !dbg !1078
  %add.ptr27 = getelementptr inbounds i8, i8* %33, i64 265, !dbg !1079
  %34 = load i8*, i8** %p, align 8, !dbg !1080
  %35 = load i64, i64* %copy_length, align 8, !dbg !1081
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr27, i8* %34, i64 %35, i32 1, i1 false), !dbg !1082
  br label %if.end28, !dbg !1083

if.end28:                                         ; preds = %if.end26, %if.end21
  %36 = load i32, i32* %tartype.addr, align 4, !dbg !1084
  %cmp29 = icmp eq i32 %36, 75, !dbg !1086
  br i1 %cmp29, label %if.then32, label %lor.lhs.false30, !dbg !1087

lor.lhs.false30:                                  ; preds = %if.end28
  %37 = load i32, i32* %tartype.addr, align 4, !dbg !1088
  %cmp31 = icmp eq i32 %37, 76, !dbg !1090
  br i1 %cmp31, label %if.then32, label %if.else35, !dbg !1091

if.then32:                                        ; preds = %lor.lhs.false30, %if.end28
  %38 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1092
  %call33 = call i8* @archive_entry_gname(%struct.archive_entry* %38), !dbg !1094
  store i8* %call33, i8** %p, align 8, !dbg !1095
  %39 = load i8*, i8** %p, align 8, !dbg !1096
  %call34 = call i64 @strlen(i8* %39) #8, !dbg !1097
  store i64 %call34, i64* %copy_length, align 8, !dbg !1098
  br label %if.end36, !dbg !1099

if.else35:                                        ; preds = %lor.lhs.false30
  %40 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1100
  %gname = getelementptr inbounds %struct.gnutar, %struct.gnutar* %40, i32 0, i32 8, !dbg !1102
  %41 = load i8*, i8** %gname, align 8, !dbg !1102
  store i8* %41, i8** %p, align 8, !dbg !1103
  %42 = load %struct.gnutar*, %struct.gnutar** %gnutar, align 8, !dbg !1104
  %gname_length = getelementptr inbounds %struct.gnutar, %struct.gnutar* %42, i32 0, i32 9, !dbg !1105
  %43 = load i64, i64* %gname_length, align 8, !dbg !1105
  store i64 %43, i64* %copy_length, align 8, !dbg !1106
  br label %if.end36

if.end36:                                         ; preds = %if.else35, %if.then32
  %44 = load i64, i64* %copy_length, align 8, !dbg !1107
  %cmp37 = icmp ugt i64 %44, 0, !dbg !1109
  br i1 %cmp37, label %if.then38, label %if.end44, !dbg !1110

if.then38:                                        ; preds = %if.end36
  %45 = load i8*, i8** %p, align 8, !dbg !1111
  %call39 = call i64 @strlen(i8* %45) #8, !dbg !1114
  %cmp40 = icmp ugt i64 %call39, 32, !dbg !1115
  br i1 %cmp40, label %if.then41, label %if.end42, !dbg !1116

if.then41:                                        ; preds = %if.then38
  store i64 32, i64* %copy_length, align 8, !dbg !1117
  br label %if.end42, !dbg !1118

if.end42:                                         ; preds = %if.then41, %if.then38
  %46 = load i8*, i8** %h.addr, align 8, !dbg !1119
  %add.ptr43 = getelementptr inbounds i8, i8* %46, i64 297, !dbg !1120
  %47 = load i8*, i8** %p, align 8, !dbg !1121
  %48 = load i64, i64* %copy_length, align 8, !dbg !1122
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr43, i8* %47, i64 %48, i32 1, i1 false), !dbg !1123
  br label %if.end44, !dbg !1124

if.end44:                                         ; preds = %if.end42, %if.end36
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1125
  %call45 = call i32 @archive_entry_mode(%struct.archive_entry* %49), !dbg !1126
  %and = and i32 %call45, 4095, !dbg !1127
  %conv = zext i32 %and to i64, !dbg !1126
  %50 = load i8*, i8** %h.addr, align 8, !dbg !1128
  %add.ptr46 = getelementptr inbounds i8, i8* %50, i64 100, !dbg !1129
  %call47 = call i32 @format_octal(i64 %conv, i8* %add.ptr46, i32 7), !dbg !1130
  %51 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1132
  %call48 = call i64 @archive_entry_uid(%struct.archive_entry* %51), !dbg !1134
  %52 = load i8*, i8** %h.addr, align 8, !dbg !1135
  %add.ptr49 = getelementptr inbounds i8, i8* %52, i64 108, !dbg !1136
  %call50 = call i32 @format_number(i64 %call48, i8* %add.ptr49, i32 7, i32 8), !dbg !1137
  %tobool = icmp ne i32 %call50, 0, !dbg !1139
  br i1 %tobool, label %if.then51, label %if.end53, !dbg !1140

if.then51:                                        ; preds = %if.end44
  %53 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1141
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %53, i32 0, i32 0, !dbg !1143
  %54 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1144
  %call52 = call i64 @archive_entry_uid(%struct.archive_entry* %54), !dbg !1145
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 34, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.19, i32 0, i32 0), i64 %call52), !dbg !1146
  store i32 -25, i32* %ret, align 4, !dbg !1147
  br label %if.end53, !dbg !1148

if.end53:                                         ; preds = %if.then51, %if.end44
  %55 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1149
  %call54 = call i64 @archive_entry_gid(%struct.archive_entry* %55), !dbg !1151
  %56 = load i8*, i8** %h.addr, align 8, !dbg !1152
  %add.ptr55 = getelementptr inbounds i8, i8* %56, i64 116, !dbg !1153
  %call56 = call i32 @format_number(i64 %call54, i8* %add.ptr55, i32 7, i32 8), !dbg !1154
  %tobool57 = icmp ne i32 %call56, 0, !dbg !1156
  br i1 %tobool57, label %if.then58, label %if.end61, !dbg !1157

if.then58:                                        ; preds = %if.end53
  %57 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1158
  %archive59 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %57, i32 0, i32 0, !dbg !1160
  %58 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1161
  %call60 = call i64 @archive_entry_gid(%struct.archive_entry* %58), !dbg !1162
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive59, i32 34, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.20, i32 0, i32 0), i64 %call60), !dbg !1163
  store i32 -25, i32* %ret, align 4, !dbg !1164
  br label %if.end61, !dbg !1165

if.end61:                                         ; preds = %if.then58, %if.end53
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1166
  %call62 = call i64 @archive_entry_size(%struct.archive_entry* %59), !dbg !1168
  %60 = load i8*, i8** %h.addr, align 8, !dbg !1169
  %add.ptr63 = getelementptr inbounds i8, i8* %60, i64 124, !dbg !1170
  %call64 = call i32 @format_number(i64 %call62, i8* %add.ptr63, i32 11, i32 12), !dbg !1171
  %tobool65 = icmp ne i32 %call64, 0, !dbg !1173
  br i1 %tobool65, label %if.then66, label %if.end68, !dbg !1174

if.then66:                                        ; preds = %if.end61
  %61 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1175
  %archive67 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %61, i32 0, i32 0, !dbg !1177
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive67, i32 34, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.21, i32 0, i32 0)), !dbg !1178
  store i32 -25, i32* %ret, align 4, !dbg !1179
  br label %if.end68, !dbg !1180

if.end68:                                         ; preds = %if.then66, %if.end61
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1181
  %call69 = call i64 @archive_entry_mtime(%struct.archive_entry* %62), !dbg !1182
  %63 = load i8*, i8** %h.addr, align 8, !dbg !1183
  %add.ptr70 = getelementptr inbounds i8, i8* %63, i64 136, !dbg !1184
  %call71 = call i32 @format_octal(i64 %call69, i8* %add.ptr70, i32 11), !dbg !1185
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1186
  %call72 = call i32 @archive_entry_filetype(%struct.archive_entry* %64), !dbg !1188
  %cmp73 = icmp eq i32 %call72, 24576, !dbg !1189
  br i1 %cmp73, label %if.then79, label %lor.lhs.false75, !dbg !1190

lor.lhs.false75:                                  ; preds = %if.end68
  %65 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1191
  %call76 = call i32 @archive_entry_filetype(%struct.archive_entry* %65), !dbg !1193
  %cmp77 = icmp eq i32 %call76, 8192, !dbg !1194
  br i1 %cmp77, label %if.then79, label %if.end94, !dbg !1195

if.then79:                                        ; preds = %lor.lhs.false75, %if.end68
  %66 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1196
  %call80 = call i64 @archive_entry_rdevmajor(%struct.archive_entry* %66), !dbg !1199
  %67 = load i8*, i8** %h.addr, align 8, !dbg !1200
  %add.ptr81 = getelementptr inbounds i8, i8* %67, i64 329, !dbg !1201
  %call82 = call i32 @format_octal(i64 %call80, i8* %add.ptr81, i32 6), !dbg !1202
  %tobool83 = icmp ne i32 %call82, 0, !dbg !1204
  br i1 %tobool83, label %if.then84, label %if.end86, !dbg !1205

if.then84:                                        ; preds = %if.then79
  %68 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1206
  %archive85 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %68, i32 0, i32 0, !dbg !1208
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive85, i32 34, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.22, i32 0, i32 0)), !dbg !1209
  store i32 -25, i32* %ret, align 4, !dbg !1210
  br label %if.end86, !dbg !1211

if.end86:                                         ; preds = %if.then84, %if.then79
  %69 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1212
  %call87 = call i64 @archive_entry_rdevminor(%struct.archive_entry* %69), !dbg !1214
  %70 = load i8*, i8** %h.addr, align 8, !dbg !1215
  %add.ptr88 = getelementptr inbounds i8, i8* %70, i64 337, !dbg !1216
  %call89 = call i32 @format_octal(i64 %call87, i8* %add.ptr88, i32 6), !dbg !1217
  %tobool90 = icmp ne i32 %call89, 0, !dbg !1219
  br i1 %tobool90, label %if.then91, label %if.end93, !dbg !1220

if.then91:                                        ; preds = %if.end86
  %71 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1221
  %archive92 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %71, i32 0, i32 0, !dbg !1223
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive92, i32 34, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.23, i32 0, i32 0)), !dbg !1224
  store i32 -25, i32* %ret, align 4, !dbg !1225
  br label %if.end93, !dbg !1226

if.end93:                                         ; preds = %if.then91, %if.end86
  br label %if.end94, !dbg !1227

if.end94:                                         ; preds = %if.end93, %lor.lhs.false75
  %72 = load i32, i32* %tartype.addr, align 4, !dbg !1228
  %conv95 = trunc i32 %72 to i8, !dbg !1228
  %73 = load i8*, i8** %h.addr, align 8, !dbg !1229
  %arrayidx = getelementptr inbounds i8, i8* %73, i64 156, !dbg !1229
  store i8 %conv95, i8* %arrayidx, align 1, !dbg !1230
  store i32 0, i32* %checksum, align 4, !dbg !1231
  store i32 0, i32* %i, align 4, !dbg !1232
  br label %for.cond, !dbg !1234

for.cond:                                         ; preds = %for.inc, %if.end94
  %74 = load i32, i32* %i, align 4, !dbg !1235
  %cmp96 = icmp slt i32 %74, 512, !dbg !1238
  br i1 %cmp96, label %for.body, label %for.end, !dbg !1239

for.body:                                         ; preds = %for.cond
  %75 = load i32, i32* %i, align 4, !dbg !1240
  %idxprom = sext i32 %75 to i64, !dbg !1241
  %76 = load i8*, i8** %h.addr, align 8, !dbg !1241
  %arrayidx98 = getelementptr inbounds i8, i8* %76, i64 %idxprom, !dbg !1241
  %77 = load i8, i8* %arrayidx98, align 1, !dbg !1241
  %conv99 = sext i8 %77 to i32, !dbg !1242
  %and100 = and i32 255, %conv99, !dbg !1243
  %78 = load i32, i32* %checksum, align 4, !dbg !1244
  %add = add i32 %78, %and100, !dbg !1244
  store i32 %add, i32* %checksum, align 4, !dbg !1244
  br label %for.inc, !dbg !1245

for.inc:                                          ; preds = %for.body
  %79 = load i32, i32* %i, align 4, !dbg !1246
  %inc = add nsw i32 %79, 1, !dbg !1246
  store i32 %inc, i32* %i, align 4, !dbg !1246
  br label %for.cond, !dbg !1248

for.end:                                          ; preds = %for.cond
  %80 = load i8*, i8** %h.addr, align 8, !dbg !1249
  %arrayidx101 = getelementptr inbounds i8, i8* %80, i64 154, !dbg !1249
  store i8 0, i8* %arrayidx101, align 1, !dbg !1250
  %81 = load i32, i32* %checksum, align 4, !dbg !1251
  %conv102 = zext i32 %81 to i64, !dbg !1251
  %82 = load i8*, i8** %h.addr, align 8, !dbg !1252
  %add.ptr103 = getelementptr inbounds i8, i8* %82, i64 148, !dbg !1253
  %call104 = call i32 @format_octal(i64 %conv102, i8* %add.ptr103, i32 6), !dbg !1254
  %83 = load i32, i32* %ret, align 4, !dbg !1255
  ret i32 %83, !dbg !1256
}

declare void @archive_entry_free(%struct.archive_entry*) #3

declare i32 @archive_entry_mode(%struct.archive_entry*) #3

declare i64 @archive_entry_size(%struct.archive_entry*) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal i32 @format_octal(i64 %v, i8* %p, i32 %s) #0 !dbg !224 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %len = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1257, metadata !240), !dbg !1258
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1259, metadata !240), !dbg !1260
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1261, metadata !240), !dbg !1262
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1263, metadata !240), !dbg !1264
  %0 = load i32, i32* %s.addr, align 4, !dbg !1265
  store i32 %0, i32* %len, align 4, !dbg !1264
  %1 = load i64, i64* %v.addr, align 8, !dbg !1266
  %cmp = icmp slt i64 %1, 0, !dbg !1268
  br i1 %cmp, label %if.then, label %if.end, !dbg !1269

if.then:                                          ; preds = %entry
  store i64 0, i64* %v.addr, align 8, !dbg !1270
  br label %if.end, !dbg !1271

if.end:                                           ; preds = %if.then, %entry
  %2 = load i32, i32* %s.addr, align 4, !dbg !1272
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1273
  %idx.ext = sext i32 %2 to i64, !dbg !1273
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 %idx.ext, !dbg !1273
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1273
  br label %while.cond, !dbg !1274

while.cond:                                       ; preds = %while.body, %if.end
  %4 = load i32, i32* %s.addr, align 4, !dbg !1275
  %dec = add nsw i32 %4, -1, !dbg !1275
  store i32 %dec, i32* %s.addr, align 4, !dbg !1275
  %cmp1 = icmp sgt i32 %4, 0, !dbg !1277
  br i1 %cmp1, label %while.body, label %while.end, !dbg !1278

while.body:                                       ; preds = %while.cond
  %5 = load i64, i64* %v.addr, align 8, !dbg !1279
  %and = and i64 %5, 7, !dbg !1281
  %add = add nsw i64 48, %and, !dbg !1282
  %conv = trunc i64 %add to i8, !dbg !1283
  %6 = load i8*, i8** %p.addr, align 8, !dbg !1284
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 -1, !dbg !1284
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1284
  store i8 %conv, i8* %incdec.ptr, align 1, !dbg !1285
  %7 = load i64, i64* %v.addr, align 8, !dbg !1286
  %shr = ashr i64 %7, 3, !dbg !1286
  store i64 %shr, i64* %v.addr, align 8, !dbg !1286
  br label %while.cond, !dbg !1287

while.end:                                        ; preds = %while.cond
  %8 = load i64, i64* %v.addr, align 8, !dbg !1289
  %cmp2 = icmp eq i64 %8, 0, !dbg !1291
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !1292

if.then4:                                         ; preds = %while.end
  store i32 0, i32* %retval, align 4, !dbg !1293
  br label %return, !dbg !1293

if.end5:                                          ; preds = %while.end
  br label %while.cond6, !dbg !1294

while.cond6:                                      ; preds = %while.body10, %if.end5
  %9 = load i32, i32* %len, align 4, !dbg !1295
  %dec7 = add nsw i32 %9, -1, !dbg !1295
  store i32 %dec7, i32* %len, align 4, !dbg !1295
  %cmp8 = icmp sgt i32 %9, 0, !dbg !1296
  br i1 %cmp8, label %while.body10, label %while.end12, !dbg !1297

while.body10:                                     ; preds = %while.cond6
  %10 = load i8*, i8** %p.addr, align 8, !dbg !1298
  %incdec.ptr11 = getelementptr inbounds i8, i8* %10, i32 1, !dbg !1298
  store i8* %incdec.ptr11, i8** %p.addr, align 8, !dbg !1298
  store i8 55, i8* %10, align 1, !dbg !1299
  br label %while.cond6, !dbg !1300

while.end12:                                      ; preds = %while.cond6
  store i32 -1, i32* %retval, align 4, !dbg !1301
  br label %return, !dbg !1301

return:                                           ; preds = %while.end12, %if.then4
  %11 = load i32, i32* %retval, align 4, !dbg !1302
  ret i32 %11, !dbg !1302
}

; Function Attrs: nounwind uwtable
define internal i32 @format_number(i64 %v, i8* %p, i32 %s, i32 %maxsize) #0 !dbg !227 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %maxsize.addr = alloca i32, align 4
  %limit = alloca i64, align 8
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1303, metadata !240), !dbg !1304
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1305, metadata !240), !dbg !1306
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1307, metadata !240), !dbg !1308
  store i32 %maxsize, i32* %maxsize.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %maxsize.addr, metadata !1309, metadata !240), !dbg !1310
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !1311, metadata !240), !dbg !1312
  %0 = load i32, i32* %s.addr, align 4, !dbg !1313
  %mul = mul nsw i32 %0, 3, !dbg !1314
  %sh_prom = zext i32 %mul to i64, !dbg !1315
  %shl = shl i64 1, %sh_prom, !dbg !1315
  store i64 %shl, i64* %limit, align 8, !dbg !1312
  %1 = load i64, i64* %v.addr, align 8, !dbg !1316
  %2 = load i64, i64* %limit, align 8, !dbg !1318
  %cmp = icmp slt i64 %1, %2, !dbg !1319
  br i1 %cmp, label %if.then, label %if.end, !dbg !1320

if.then:                                          ; preds = %entry
  %3 = load i64, i64* %v.addr, align 8, !dbg !1321
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1322
  %5 = load i32, i32* %s.addr, align 4, !dbg !1323
  %call = call i32 @format_octal(i64 %3, i8* %4, i32 %5), !dbg !1324
  store i32 %call, i32* %retval, align 4, !dbg !1325
  br label %return, !dbg !1325

if.end:                                           ; preds = %entry
  %6 = load i64, i64* %v.addr, align 8, !dbg !1326
  %7 = load i8*, i8** %p.addr, align 8, !dbg !1327
  %8 = load i32, i32* %maxsize.addr, align 4, !dbg !1328
  %call1 = call i32 @format_256(i64 %6, i8* %7, i32 %8), !dbg !1329
  store i32 %call1, i32* %retval, align 4, !dbg !1330
  br label %return, !dbg !1330

return:                                           ; preds = %if.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !1331
  ret i32 %9, !dbg !1331
}

declare i64 @archive_entry_uid(%struct.archive_entry*) #3

declare i64 @archive_entry_gid(%struct.archive_entry*) #3

declare i64 @archive_entry_mtime(%struct.archive_entry*) #3

declare i64 @archive_entry_rdevmajor(%struct.archive_entry*) #3

declare i64 @archive_entry_rdevminor(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define internal i32 @format_256(i64 %v, i8* %p, i32 %s) #0 !dbg !230 {
entry:
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1332, metadata !240), !dbg !1333
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1334, metadata !240), !dbg !1335
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1336, metadata !240), !dbg !1337
  %0 = load i32, i32* %s.addr, align 4, !dbg !1338
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1339
  %idx.ext = sext i32 %0 to i64, !dbg !1339
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !1339
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1339
  br label %while.cond, !dbg !1340

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i32, i32* %s.addr, align 4, !dbg !1341
  %dec = add nsw i32 %2, -1, !dbg !1341
  store i32 %dec, i32* %s.addr, align 4, !dbg !1341
  %cmp = icmp sgt i32 %2, 0, !dbg !1343
  br i1 %cmp, label %while.body, label %while.end, !dbg !1344

while.body:                                       ; preds = %while.cond
  %3 = load i64, i64* %v.addr, align 8, !dbg !1345
  %and = and i64 %3, 255, !dbg !1347
  %conv = trunc i64 %and to i8, !dbg !1348
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1349
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 -1, !dbg !1349
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1349
  store i8 %conv, i8* %incdec.ptr, align 1, !dbg !1350
  %5 = load i64, i64* %v.addr, align 8, !dbg !1351
  %shr = ashr i64 %5, 8, !dbg !1351
  store i64 %shr, i64* %v.addr, align 8, !dbg !1351
  br label %while.cond, !dbg !1352

while.end:                                        ; preds = %while.cond
  %6 = load i8*, i8** %p.addr, align 8, !dbg !1354
  %7 = load i8, i8* %6, align 1, !dbg !1355
  %conv1 = sext i8 %7 to i32, !dbg !1355
  %or = or i32 %conv1, 128, !dbg !1355
  %conv2 = trunc i32 %or to i8, !dbg !1355
  store i8 %conv2, i8* %6, align 1, !dbg !1355
  ret i32 0, !dbg !1356
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!236, !237}
!llvm.ident = !{!238}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !213, globals: !231)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_gnutar.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !192, !124, !45, !209, !38, !47, !52, !212, !13, !82}
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
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "gnutar", file: !1, line: 50, size: 832, align: 64, elements: !194)
!194 = !{!195, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !193, file: !1, line: 51, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !193, file: !1, line: 52, baseType: !196, size: 64, align: 64, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "linkname", scope: !193, file: !1, line: 53, baseType: !80, size: 64, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "linkname_length", scope: !193, file: !1, line: 54, baseType: !45, size: 64, align: 64, offset: 192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "pathname", scope: !193, file: !1, line: 55, baseType: !80, size: 64, align: 64, offset: 256)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "pathname_length", scope: !193, file: !1, line: 56, baseType: !45, size: 64, align: 64, offset: 320)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "uname", scope: !193, file: !1, line: 57, baseType: !80, size: 64, align: 64, offset: 384)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "uname_length", scope: !193, file: !1, line: 58, baseType: !45, size: 64, align: 64, offset: 448)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "gname", scope: !193, file: !1, line: 59, baseType: !80, size: 64, align: 64, offset: 512)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "gname_length", scope: !193, file: !1, line: 60, baseType: !45, size: 64, align: 64, offset: 576)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !193, file: !1, line: 61, baseType: !102, size: 64, align: 64, offset: 640)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !193, file: !1, line: 62, baseType: !102, size: 64, align: 64, offset: 704)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !193, file: !1, line: 63, baseType: !23, size: 32, align: 32, offset: 768)
!209 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !210, line: 70, baseType: !211)
!210 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!212 = !DIDerivedType(tag: DW_TAG_typedef, name: "intmax_t", file: !53, line: 134, baseType: !42)
!213 = !{!214, !215, !216, !217, !218, !219, !220, !221, !224, !227, !230}
!214 = distinct !DISubprogram(name: "archive_write_set_format_gnutar", scope: !1, file: !1, line: 173, type: !21, isLocal: false, isDefinition: true, scopeLine: 174, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = distinct !DISubprogram(name: "archive_write_gnutar_options", scope: !1, file: !1, line: 198, type: !172, isLocal: true, isDefinition: true, scopeLine: 200, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!216 = distinct !DISubprogram(name: "archive_write_gnutar_close", scope: !1, file: !1, line: 227, type: !168, isLocal: true, isDefinition: true, scopeLine: 228, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!217 = distinct !DISubprogram(name: "archive_write_gnutar_free", scope: !1, file: !1, line: 233, type: !168, isLocal: true, isDefinition: true, scopeLine: 234, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!218 = distinct !DISubprogram(name: "archive_write_gnutar_finish_entry", scope: !1, file: !1, line: 244, type: !168, isLocal: true, isDefinition: true, scopeLine: 245, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!219 = distinct !DISubprogram(name: "archive_write_gnutar_data", scope: !1, file: !1, line: 257, type: !181, isLocal: true, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = distinct !DISubprogram(name: "archive_write_gnutar_header", scope: !1, file: !1, line: 273, type: !177, isLocal: true, isDefinition: true, scopeLine: 275, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_format_gnutar_header", scope: !1, file: !1, line: 574, type: !222, isLocal: true, isDefinition: true, scopeLine: 576, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = !DISubroutineType(types: !223)
!223 = !{!23, !4, !95, !30, !23}
!224 = distinct !DISubprogram(name: "format_octal", scope: !1, file: !1, line: 741, type: !225, isLocal: true, isDefinition: true, scopeLine: 742, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!225 = !DISubroutineType(types: !226)
!226 = !{!23, !52, !95, !23}
!227 = distinct !DISubprogram(name: "format_number", scope: !1, file: !1, line: 713, type: !228, isLocal: true, isDefinition: true, scopeLine: 714, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!228 = !DISubroutineType(types: !229)
!229 = !{!23, !52, !95, !23, !23}
!230 = distinct !DISubprogram(name: "format_256", scope: !1, file: !1, line: 726, type: !225, isLocal: true, isDefinition: true, scopeLine: 727, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!231 = !{!232}
!232 = !DIGlobalVariable(name: "template_header", scope: !0, file: !1, line: 110, type: !233, isLocal: true, isDefinition: true, variable: [512 x i8]* @template_header)
!233 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 4096, align: 8, elements: !234)
!234 = !{!235}
!235 = !DISubrange(count: 512)
!236 = !{i32 2, !"Dwarf Version", i32 4}
!237 = !{i32 2, !"Debug Info Version", i32 3}
!238 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!239 = !DILocalVariable(name: "_a", arg: 1, scope: !214, file: !1, line: 173, type: !24)
!240 = !DIExpression()
!241 = !DILocation(line: 173, column: 49, scope: !214)
!242 = !DILocalVariable(name: "a", scope: !214, file: !1, line: 175, type: !4)
!243 = !DILocation(line: 175, column: 24, scope: !214)
!244 = !DILocation(line: 175, column: 52, scope: !214)
!245 = !DILocation(line: 175, column: 28, scope: !214)
!246 = !DILocalVariable(name: "gnutar", scope: !214, file: !1, line: 176, type: !192)
!247 = !DILocation(line: 176, column: 17, scope: !214)
!248 = !DILocation(line: 178, column: 28, scope: !214)
!249 = !DILocation(line: 178, column: 11, scope: !214)
!250 = !DILocation(line: 178, column: 9, scope: !214)
!251 = !DILocation(line: 179, column: 6, scope: !252)
!252 = distinct !DILexicalBlock(scope: !214, file: !1, line: 179, column: 6)
!253 = !DILocation(line: 179, column: 13, scope: !252)
!254 = !DILocation(line: 179, column: 6, scope: !214)
!255 = !DILocation(line: 180, column: 22, scope: !256)
!256 = distinct !DILexicalBlock(scope: !252, file: !1, line: 179, column: 22)
!257 = !DILocation(line: 180, column: 25, scope: !256)
!258 = !DILocation(line: 180, column: 3, scope: !256)
!259 = !DILocation(line: 182, column: 3, scope: !256)
!260 = !DILocation(line: 184, column: 19, scope: !214)
!261 = !DILocation(line: 184, column: 2, scope: !214)
!262 = !DILocation(line: 184, column: 5, scope: !214)
!263 = !DILocation(line: 184, column: 17, scope: !214)
!264 = !DILocation(line: 185, column: 2, scope: !214)
!265 = !DILocation(line: 185, column: 5, scope: !214)
!266 = !DILocation(line: 185, column: 17, scope: !214)
!267 = !DILocation(line: 186, column: 2, scope: !214)
!268 = !DILocation(line: 186, column: 5, scope: !214)
!269 = !DILocation(line: 186, column: 20, scope: !214)
!270 = !DILocation(line: 187, column: 2, scope: !214)
!271 = !DILocation(line: 187, column: 5, scope: !214)
!272 = !DILocation(line: 187, column: 25, scope: !214)
!273 = !DILocation(line: 188, column: 2, scope: !214)
!274 = !DILocation(line: 188, column: 5, scope: !214)
!275 = !DILocation(line: 188, column: 23, scope: !214)
!276 = !DILocation(line: 189, column: 2, scope: !214)
!277 = !DILocation(line: 189, column: 5, scope: !214)
!278 = !DILocation(line: 189, column: 18, scope: !214)
!279 = !DILocation(line: 190, column: 2, scope: !214)
!280 = !DILocation(line: 190, column: 5, scope: !214)
!281 = !DILocation(line: 190, column: 17, scope: !214)
!282 = !DILocation(line: 191, column: 2, scope: !214)
!283 = !DILocation(line: 191, column: 5, scope: !214)
!284 = !DILocation(line: 191, column: 25, scope: !214)
!285 = !DILocation(line: 192, column: 2, scope: !214)
!286 = !DILocation(line: 192, column: 5, scope: !214)
!287 = !DILocation(line: 192, column: 13, scope: !214)
!288 = !DILocation(line: 192, column: 28, scope: !214)
!289 = !DILocation(line: 193, column: 2, scope: !214)
!290 = !DILocation(line: 193, column: 5, scope: !214)
!291 = !DILocation(line: 193, column: 13, scope: !214)
!292 = !DILocation(line: 193, column: 33, scope: !214)
!293 = !DILocation(line: 194, column: 2, scope: !214)
!294 = !DILocation(line: 195, column: 1, scope: !214)
!295 = !DILocalVariable(name: "a", arg: 1, scope: !215, file: !1, line: 198, type: !4)
!296 = !DILocation(line: 198, column: 52, scope: !215)
!297 = !DILocalVariable(name: "key", arg: 2, scope: !215, file: !1, line: 198, type: !80)
!298 = !DILocation(line: 198, column: 67, scope: !215)
!299 = !DILocalVariable(name: "val", arg: 3, scope: !215, file: !1, line: 199, type: !80)
!300 = !DILocation(line: 199, column: 17, scope: !215)
!301 = !DILocalVariable(name: "gnutar", scope: !215, file: !1, line: 201, type: !192)
!302 = !DILocation(line: 201, column: 17, scope: !215)
!303 = !DILocation(line: 201, column: 43, scope: !215)
!304 = !DILocation(line: 201, column: 46, scope: !215)
!305 = !DILocation(line: 201, column: 26, scope: !215)
!306 = !DILocalVariable(name: "ret", scope: !215, file: !1, line: 202, type: !23)
!307 = !DILocation(line: 202, column: 6, scope: !215)
!308 = !DILocation(line: 204, column: 13, scope: !309)
!309 = distinct !DILexicalBlock(scope: !215, file: !1, line: 204, column: 6)
!310 = !DILocation(line: 204, column: 6, scope: !309)
!311 = !DILocation(line: 204, column: 33, scope: !309)
!312 = !DILocation(line: 204, column: 6, scope: !215)
!313 = !DILocation(line: 205, column: 7, scope: !314)
!314 = distinct !DILexicalBlock(scope: !315, file: !1, line: 205, column: 7)
!315 = distinct !DILexicalBlock(scope: !309, file: !1, line: 204, column: 39)
!316 = !DILocation(line: 205, column: 11, scope: !314)
!317 = !DILocation(line: 205, column: 19, scope: !314)
!318 = !DILocation(line: 205, column: 22, scope: !319)
!319 = !DILexicalBlockFile(scope: !314, file: !1, discriminator: 1)
!320 = !DILocation(line: 205, column: 29, scope: !319)
!321 = !DILocation(line: 205, column: 7, scope: !319)
!322 = !DILocation(line: 206, column: 23, scope: !314)
!323 = !DILocation(line: 206, column: 26, scope: !314)
!324 = !DILocation(line: 208, column: 8, scope: !314)
!325 = !DILocation(line: 208, column: 11, scope: !314)
!326 = !DILocation(line: 206, column: 4, scope: !314)
!327 = !DILocation(line: 211, column: 9, scope: !328)
!328 = distinct !DILexicalBlock(scope: !314, file: !1, line: 209, column: 8)
!329 = !DILocation(line: 211, column: 12, scope: !328)
!330 = !DILocation(line: 211, column: 21, scope: !328)
!331 = !DILocation(line: 210, column: 24, scope: !328)
!332 = !DILocation(line: 210, column: 4, scope: !328)
!333 = !DILocation(line: 210, column: 12, scope: !328)
!334 = !DILocation(line: 210, column: 22, scope: !328)
!335 = !DILocation(line: 212, column: 8, scope: !336)
!336 = distinct !DILexicalBlock(scope: !328, file: !1, line: 212, column: 8)
!337 = !DILocation(line: 212, column: 16, scope: !336)
!338 = !DILocation(line: 212, column: 26, scope: !336)
!339 = !DILocation(line: 212, column: 8, scope: !328)
!340 = !DILocation(line: 213, column: 9, scope: !336)
!341 = !DILocation(line: 213, column: 5, scope: !336)
!342 = !DILocation(line: 215, column: 9, scope: !336)
!343 = !DILocation(line: 217, column: 11, scope: !315)
!344 = !DILocation(line: 217, column: 3, scope: !315)
!345 = !DILocation(line: 223, column: 2, scope: !215)
!346 = !DILocation(line: 224, column: 1, scope: !215)
!347 = !DILocalVariable(name: "a", arg: 1, scope: !220, file: !1, line: 273, type: !4)
!348 = !DILocation(line: 273, column: 51, scope: !220)
!349 = !DILocalVariable(name: "entry", arg: 2, scope: !220, file: !1, line: 274, type: !30)
!350 = !DILocation(line: 274, column: 28, scope: !220)
!351 = !DILocalVariable(name: "buff", scope: !220, file: !1, line: 276, type: !352)
!352 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 4096, align: 8, elements: !234)
!353 = !DILocation(line: 276, column: 7, scope: !220)
!354 = !DILocalVariable(name: "r", scope: !220, file: !1, line: 277, type: !23)
!355 = !DILocation(line: 277, column: 6, scope: !220)
!356 = !DILocalVariable(name: "ret", scope: !220, file: !1, line: 277, type: !23)
!357 = !DILocation(line: 277, column: 9, scope: !220)
!358 = !DILocalVariable(name: "ret2", scope: !220, file: !1, line: 277, type: !23)
!359 = !DILocation(line: 277, column: 14, scope: !220)
!360 = !DILocalVariable(name: "tartype", scope: !220, file: !1, line: 278, type: !23)
!361 = !DILocation(line: 278, column: 6, scope: !220)
!362 = !DILocalVariable(name: "gnutar", scope: !220, file: !1, line: 279, type: !192)
!363 = !DILocation(line: 279, column: 17, scope: !220)
!364 = !DILocalVariable(name: "sconv", scope: !220, file: !1, line: 280, type: !102)
!365 = !DILocation(line: 280, column: 30, scope: !220)
!366 = !DILocalVariable(name: "entry_main", scope: !220, file: !1, line: 281, type: !30)
!367 = !DILocation(line: 281, column: 24, scope: !220)
!368 = !DILocation(line: 283, column: 28, scope: !220)
!369 = !DILocation(line: 283, column: 31, scope: !220)
!370 = !DILocation(line: 283, column: 11, scope: !220)
!371 = !DILocation(line: 283, column: 9, scope: !220)
!372 = !DILocation(line: 286, column: 6, scope: !373)
!373 = distinct !DILexicalBlock(scope: !220, file: !1, line: 286, column: 6)
!374 = !DILocation(line: 286, column: 14, scope: !373)
!375 = !DILocation(line: 286, column: 24, scope: !373)
!376 = !DILocation(line: 286, column: 6, scope: !220)
!377 = !DILocation(line: 287, column: 8, scope: !378)
!378 = distinct !DILexicalBlock(scope: !379, file: !1, line: 287, column: 7)
!379 = distinct !DILexicalBlock(scope: !373, file: !1, line: 286, column: 33)
!380 = !DILocation(line: 287, column: 16, scope: !378)
!381 = !DILocation(line: 287, column: 7, scope: !379)
!382 = !DILocation(line: 290, column: 7, scope: !383)
!383 = distinct !DILexicalBlock(scope: !378, file: !1, line: 287, column: 41)
!384 = !DILocation(line: 290, column: 10, scope: !383)
!385 = !DILocation(line: 289, column: 8, scope: !383)
!386 = !DILocation(line: 288, column: 4, scope: !383)
!387 = !DILocation(line: 288, column: 12, scope: !383)
!388 = !DILocation(line: 288, column: 26, scope: !383)
!389 = !DILocation(line: 291, column: 4, scope: !383)
!390 = !DILocation(line: 291, column: 12, scope: !383)
!391 = !DILocation(line: 291, column: 36, scope: !383)
!392 = !DILocation(line: 292, column: 3, scope: !383)
!393 = !DILocation(line: 293, column: 11, scope: !379)
!394 = !DILocation(line: 293, column: 19, scope: !379)
!395 = !DILocation(line: 293, column: 9, scope: !379)
!396 = !DILocation(line: 294, column: 2, scope: !379)
!397 = !DILocation(line: 295, column: 11, scope: !373)
!398 = !DILocation(line: 295, column: 19, scope: !373)
!399 = !DILocation(line: 295, column: 9, scope: !373)
!400 = !DILocation(line: 298, column: 29, scope: !401)
!401 = distinct !DILexicalBlock(scope: !220, file: !1, line: 298, column: 6)
!402 = !DILocation(line: 298, column: 6, scope: !401)
!403 = !DILocation(line: 298, column: 36, scope: !401)
!404 = !DILocation(line: 298, column: 44, scope: !401)
!405 = !DILocation(line: 299, column: 28, scope: !401)
!406 = !DILocation(line: 299, column: 6, scope: !401)
!407 = !DILocation(line: 299, column: 35, scope: !401)
!408 = !DILocation(line: 299, column: 43, scope: !401)
!409 = !DILocation(line: 300, column: 31, scope: !401)
!410 = !DILocation(line: 300, column: 8, scope: !401)
!411 = !DILocation(line: 300, column: 38, scope: !401)
!412 = !DILocation(line: 298, column: 6, scope: !413)
!413 = !DILexicalBlockFile(scope: !220, file: !1, discriminator: 1)
!414 = !DILocation(line: 301, column: 26, scope: !401)
!415 = !DILocation(line: 301, column: 3, scope: !401)
!416 = !DILocation(line: 303, column: 41, scope: !417)
!417 = distinct !DILexicalBlock(scope: !220, file: !1, line: 303, column: 6)
!418 = !DILocation(line: 303, column: 18, scope: !417)
!419 = !DILocation(line: 303, column: 15, scope: !417)
!420 = !DILocation(line: 303, column: 6, scope: !220)
!421 = !DILocalVariable(name: "p", scope: !422, file: !1, line: 304, type: !80)
!422 = distinct !DILexicalBlock(scope: !417, file: !1, line: 303, column: 49)
!423 = !DILocation(line: 304, column: 15, scope: !422)
!424 = !DILocalVariable(name: "path_length", scope: !422, file: !1, line: 305, type: !45)
!425 = !DILocation(line: 305, column: 10, scope: !422)
!426 = !DILocation(line: 336, column: 31, scope: !422)
!427 = !DILocation(line: 336, column: 8, scope: !422)
!428 = !DILocation(line: 336, column: 6, scope: !422)
!429 = !DILocation(line: 342, column: 7, scope: !430)
!430 = distinct !DILexicalBlock(scope: !422, file: !1, line: 342, column: 7)
!431 = !DILocation(line: 342, column: 9, scope: !430)
!432 = !DILocation(line: 342, column: 17, scope: !430)
!433 = !DILocation(line: 342, column: 29, scope: !434)
!434 = !DILexicalBlockFile(scope: !430, file: !1, discriminator: 1)
!435 = !DILocation(line: 342, column: 22, scope: !434)
!436 = !DILocation(line: 342, column: 32, scope: !434)
!437 = !DILocation(line: 342, column: 20, scope: !434)
!438 = !DILocation(line: 342, column: 37, scope: !434)
!439 = !DILocation(line: 342, column: 7, scope: !434)
!440 = !DILocalVariable(name: "as", scope: !441, file: !1, line: 343, type: !91)
!441 = distinct !DILexicalBlock(scope: !430, file: !1, line: 342, column: 45)
!442 = !DILocation(line: 343, column: 26, scope: !441)
!443 = !DILocation(line: 345, column: 4, scope: !441)
!444 = !DILocation(line: 345, column: 4, scope: !445)
!445 = !DILexicalBlockFile(scope: !446, file: !1, discriminator: 1)
!446 = distinct !DILexicalBlock(scope: !441, file: !1, line: 345, column: 4)
!447 = !DILocation(line: 346, column: 25, scope: !441)
!448 = !DILocation(line: 346, column: 18, scope: !441)
!449 = !DILocation(line: 346, column: 16, scope: !441)
!450 = !DILocation(line: 348, column: 8, scope: !451)
!451 = distinct !DILexicalBlock(scope: !441, file: !1, line: 347, column: 8)
!452 = !DILocation(line: 348, column: 20, scope: !451)
!453 = !DILocation(line: 347, column: 8, scope: !451)
!454 = !DILocation(line: 348, column: 25, scope: !451)
!455 = !DILocation(line: 347, column: 8, scope: !441)
!456 = !DILocation(line: 349, column: 24, scope: !457)
!457 = distinct !DILexicalBlock(scope: !451, file: !1, line: 348, column: 34)
!458 = !DILocation(line: 349, column: 27, scope: !457)
!459 = !DILocation(line: 349, column: 5, scope: !457)
!460 = !DILocation(line: 351, column: 5, scope: !457)
!461 = !DILocation(line: 352, column: 5, scope: !457)
!462 = !DILocation(line: 363, column: 4, scope: !441)
!463 = !DILocation(line: 364, column: 4, scope: !441)
!464 = !DILocation(line: 365, column: 32, scope: !441)
!465 = !DILocation(line: 365, column: 42, scope: !441)
!466 = !DILocation(line: 365, column: 4, scope: !441)
!467 = !DILocation(line: 366, column: 4, scope: !441)
!468 = !DILocation(line: 367, column: 3, scope: !441)
!469 = !DILocation(line: 368, column: 2, scope: !422)
!470 = !DILocation(line: 384, column: 13, scope: !220)
!471 = !DILocation(line: 386, column: 31, scope: !220)
!472 = !DILocation(line: 386, column: 40, scope: !220)
!473 = !DILocation(line: 386, column: 48, scope: !220)
!474 = !DILocation(line: 387, column: 8, scope: !220)
!475 = !DILocation(line: 387, column: 16, scope: !220)
!476 = !DILocation(line: 387, column: 34, scope: !220)
!477 = !DILocation(line: 386, column: 6, scope: !220)
!478 = !DILocation(line: 386, column: 4, scope: !220)
!479 = !DILocation(line: 388, column: 6, scope: !480)
!480 = distinct !DILexicalBlock(scope: !220, file: !1, line: 388, column: 6)
!481 = !DILocation(line: 388, column: 8, scope: !480)
!482 = !DILocation(line: 388, column: 6, scope: !220)
!483 = !DILocation(line: 389, column: 7, scope: !484)
!484 = distinct !DILexicalBlock(scope: !485, file: !1, line: 389, column: 7)
!485 = distinct !DILexicalBlock(scope: !480, file: !1, line: 388, column: 14)
!486 = !DILocation(line: 389, column: 13, scope: !484)
!487 = !DILocation(line: 389, column: 7, scope: !485)
!488 = !DILocation(line: 390, column: 23, scope: !489)
!489 = distinct !DILexicalBlock(scope: !484, file: !1, line: 389, column: 24)
!490 = !DILocation(line: 390, column: 26, scope: !489)
!491 = !DILocation(line: 390, column: 4, scope: !489)
!492 = !DILocation(line: 392, column: 8, scope: !489)
!493 = !DILocation(line: 393, column: 4, scope: !489)
!494 = !DILocation(line: 395, column: 22, scope: !485)
!495 = !DILocation(line: 395, column: 25, scope: !485)
!496 = !DILocation(line: 397, column: 30, scope: !485)
!497 = !DILocation(line: 397, column: 7, scope: !485)
!498 = !DILocation(line: 398, column: 46, scope: !485)
!499 = !DILocation(line: 398, column: 7, scope: !485)
!500 = !DILocation(line: 395, column: 3, scope: !485)
!501 = !DILocation(line: 399, column: 8, scope: !485)
!502 = !DILocation(line: 400, column: 2, scope: !485)
!503 = !DILocation(line: 401, column: 28, scope: !220)
!504 = !DILocation(line: 401, column: 37, scope: !220)
!505 = !DILocation(line: 401, column: 45, scope: !220)
!506 = !DILocation(line: 402, column: 8, scope: !220)
!507 = !DILocation(line: 402, column: 16, scope: !220)
!508 = !DILocation(line: 402, column: 31, scope: !220)
!509 = !DILocation(line: 401, column: 6, scope: !220)
!510 = !DILocation(line: 401, column: 4, scope: !220)
!511 = !DILocation(line: 403, column: 6, scope: !512)
!512 = distinct !DILexicalBlock(scope: !220, file: !1, line: 403, column: 6)
!513 = !DILocation(line: 403, column: 8, scope: !512)
!514 = !DILocation(line: 403, column: 6, scope: !220)
!515 = !DILocation(line: 404, column: 7, scope: !516)
!516 = distinct !DILexicalBlock(scope: !517, file: !1, line: 404, column: 7)
!517 = distinct !DILexicalBlock(scope: !512, file: !1, line: 403, column: 14)
!518 = !DILocation(line: 404, column: 13, scope: !516)
!519 = !DILocation(line: 404, column: 7, scope: !517)
!520 = !DILocation(line: 405, column: 23, scope: !521)
!521 = distinct !DILexicalBlock(scope: !516, file: !1, line: 404, column: 24)
!522 = !DILocation(line: 405, column: 26, scope: !521)
!523 = !DILocation(line: 405, column: 4, scope: !521)
!524 = !DILocation(line: 407, column: 8, scope: !521)
!525 = !DILocation(line: 408, column: 4, scope: !521)
!526 = !DILocation(line: 410, column: 22, scope: !517)
!527 = !DILocation(line: 410, column: 25, scope: !517)
!528 = !DILocation(line: 413, column: 27, scope: !517)
!529 = !DILocation(line: 413, column: 7, scope: !517)
!530 = !DILocation(line: 414, column: 46, scope: !517)
!531 = !DILocation(line: 414, column: 7, scope: !517)
!532 = !DILocation(line: 410, column: 3, scope: !517)
!533 = !DILocation(line: 415, column: 8, scope: !517)
!534 = !DILocation(line: 416, column: 2, scope: !517)
!535 = !DILocation(line: 417, column: 28, scope: !220)
!536 = !DILocation(line: 417, column: 37, scope: !220)
!537 = !DILocation(line: 417, column: 45, scope: !220)
!538 = !DILocation(line: 418, column: 8, scope: !220)
!539 = !DILocation(line: 418, column: 16, scope: !220)
!540 = !DILocation(line: 418, column: 31, scope: !220)
!541 = !DILocation(line: 417, column: 6, scope: !220)
!542 = !DILocation(line: 417, column: 4, scope: !220)
!543 = !DILocation(line: 419, column: 6, scope: !544)
!544 = distinct !DILexicalBlock(scope: !220, file: !1, line: 419, column: 6)
!545 = !DILocation(line: 419, column: 8, scope: !544)
!546 = !DILocation(line: 419, column: 6, scope: !220)
!547 = !DILocation(line: 420, column: 7, scope: !548)
!548 = distinct !DILexicalBlock(scope: !549, file: !1, line: 420, column: 7)
!549 = distinct !DILexicalBlock(scope: !544, file: !1, line: 419, column: 14)
!550 = !DILocation(line: 420, column: 13, scope: !548)
!551 = !DILocation(line: 420, column: 7, scope: !549)
!552 = !DILocation(line: 421, column: 23, scope: !553)
!553 = distinct !DILexicalBlock(scope: !548, file: !1, line: 420, column: 24)
!554 = !DILocation(line: 421, column: 26, scope: !553)
!555 = !DILocation(line: 421, column: 4, scope: !553)
!556 = !DILocation(line: 423, column: 8, scope: !553)
!557 = !DILocation(line: 424, column: 4, scope: !553)
!558 = !DILocation(line: 426, column: 22, scope: !549)
!559 = !DILocation(line: 426, column: 25, scope: !549)
!560 = !DILocation(line: 429, column: 27, scope: !549)
!561 = !DILocation(line: 429, column: 7, scope: !549)
!562 = !DILocation(line: 430, column: 46, scope: !549)
!563 = !DILocation(line: 430, column: 7, scope: !549)
!564 = !DILocation(line: 426, column: 3, scope: !549)
!565 = !DILocation(line: 431, column: 8, scope: !549)
!566 = !DILocation(line: 432, column: 2, scope: !549)
!567 = !DILocation(line: 435, column: 31, scope: !220)
!568 = !DILocation(line: 435, column: 40, scope: !220)
!569 = !DILocation(line: 435, column: 48, scope: !220)
!570 = !DILocation(line: 436, column: 8, scope: !220)
!571 = !DILocation(line: 436, column: 16, scope: !220)
!572 = !DILocation(line: 436, column: 34, scope: !220)
!573 = !DILocation(line: 435, column: 6, scope: !220)
!574 = !DILocation(line: 435, column: 4, scope: !220)
!575 = !DILocation(line: 437, column: 6, scope: !576)
!576 = distinct !DILexicalBlock(scope: !220, file: !1, line: 437, column: 6)
!577 = !DILocation(line: 437, column: 8, scope: !576)
!578 = !DILocation(line: 437, column: 6, scope: !220)
!579 = !DILocation(line: 438, column: 7, scope: !580)
!580 = distinct !DILexicalBlock(scope: !581, file: !1, line: 438, column: 7)
!581 = distinct !DILexicalBlock(scope: !576, file: !1, line: 437, column: 14)
!582 = !DILocation(line: 438, column: 13, scope: !580)
!583 = !DILocation(line: 438, column: 7, scope: !581)
!584 = !DILocation(line: 439, column: 23, scope: !585)
!585 = distinct !DILexicalBlock(scope: !580, file: !1, line: 438, column: 24)
!586 = !DILocation(line: 439, column: 26, scope: !585)
!587 = !DILocation(line: 439, column: 4, scope: !585)
!588 = !DILocation(line: 441, column: 8, scope: !585)
!589 = !DILocation(line: 442, column: 4, scope: !585)
!590 = !DILocation(line: 444, column: 22, scope: !581)
!591 = !DILocation(line: 444, column: 25, scope: !581)
!592 = !DILocation(line: 447, column: 30, scope: !581)
!593 = !DILocation(line: 447, column: 7, scope: !581)
!594 = !DILocation(line: 448, column: 46, scope: !581)
!595 = !DILocation(line: 448, column: 7, scope: !581)
!596 = !DILocation(line: 444, column: 3, scope: !581)
!597 = !DILocation(line: 449, column: 8, scope: !581)
!598 = !DILocation(line: 450, column: 2, scope: !581)
!599 = !DILocation(line: 451, column: 6, scope: !600)
!600 = distinct !DILexicalBlock(scope: !220, file: !1, line: 451, column: 6)
!601 = !DILocation(line: 451, column: 14, scope: !600)
!602 = !DILocation(line: 451, column: 30, scope: !600)
!603 = !DILocation(line: 451, column: 6, scope: !220)
!604 = !DILocation(line: 452, column: 31, scope: !605)
!605 = distinct !DILexicalBlock(scope: !600, file: !1, line: 451, column: 36)
!606 = !DILocation(line: 452, column: 40, scope: !605)
!607 = !DILocation(line: 452, column: 48, scope: !605)
!608 = !DILocation(line: 453, column: 9, scope: !605)
!609 = !DILocation(line: 453, column: 17, scope: !605)
!610 = !DILocation(line: 453, column: 35, scope: !605)
!611 = !DILocation(line: 452, column: 7, scope: !605)
!612 = !DILocation(line: 452, column: 5, scope: !605)
!613 = !DILocation(line: 454, column: 7, scope: !614)
!614 = distinct !DILexicalBlock(scope: !605, file: !1, line: 454, column: 7)
!615 = !DILocation(line: 454, column: 9, scope: !614)
!616 = !DILocation(line: 454, column: 7, scope: !605)
!617 = !DILocation(line: 455, column: 8, scope: !618)
!618 = distinct !DILexicalBlock(scope: !619, file: !1, line: 455, column: 8)
!619 = distinct !DILexicalBlock(scope: !614, file: !1, line: 454, column: 15)
!620 = !DILocation(line: 455, column: 14, scope: !618)
!621 = !DILocation(line: 455, column: 8, scope: !619)
!622 = !DILocation(line: 456, column: 24, scope: !623)
!623 = distinct !DILexicalBlock(scope: !618, file: !1, line: 455, column: 25)
!624 = !DILocation(line: 456, column: 27, scope: !623)
!625 = !DILocation(line: 456, column: 5, scope: !623)
!626 = !DILocation(line: 458, column: 9, scope: !623)
!627 = !DILocation(line: 459, column: 5, scope: !623)
!628 = !DILocation(line: 461, column: 23, scope: !619)
!629 = !DILocation(line: 461, column: 26, scope: !619)
!630 = !DILocation(line: 464, column: 31, scope: !619)
!631 = !DILocation(line: 464, column: 8, scope: !619)
!632 = !DILocation(line: 465, column: 47, scope: !619)
!633 = !DILocation(line: 465, column: 8, scope: !619)
!634 = !DILocation(line: 461, column: 4, scope: !619)
!635 = !DILocation(line: 466, column: 9, scope: !619)
!636 = !DILocation(line: 467, column: 3, scope: !619)
!637 = !DILocation(line: 468, column: 2, scope: !605)
!638 = !DILocation(line: 469, column: 6, scope: !639)
!639 = distinct !DILexicalBlock(scope: !220, file: !1, line: 469, column: 6)
!640 = !DILocation(line: 469, column: 14, scope: !639)
!641 = !DILocation(line: 469, column: 30, scope: !639)
!642 = !DILocation(line: 469, column: 6, scope: !220)
!643 = !DILocalVariable(name: "length", scope: !644, file: !1, line: 470, type: !45)
!644 = distinct !DILexicalBlock(scope: !639, file: !1, line: 469, column: 54)
!645 = !DILocation(line: 470, column: 10, scope: !644)
!646 = !DILocation(line: 470, column: 19, scope: !644)
!647 = !DILocation(line: 470, column: 27, scope: !644)
!648 = !DILocation(line: 470, column: 43, scope: !644)
!649 = !DILocalVariable(name: "temp", scope: !644, file: !1, line: 471, type: !30)
!650 = !DILocation(line: 471, column: 25, scope: !644)
!651 = !DILocation(line: 471, column: 52, scope: !644)
!652 = !DILocation(line: 471, column: 55, scope: !644)
!653 = !DILocation(line: 471, column: 32, scope: !644)
!654 = !DILocation(line: 475, column: 27, scope: !644)
!655 = !DILocation(line: 475, column: 3, scope: !644)
!656 = !DILocation(line: 476, column: 27, scope: !644)
!657 = !DILocation(line: 476, column: 3, scope: !644)
!658 = !DILocation(line: 478, column: 30, scope: !644)
!659 = !DILocation(line: 478, column: 3, scope: !644)
!660 = !DILocation(line: 479, column: 26, scope: !644)
!661 = !DILocation(line: 479, column: 32, scope: !644)
!662 = !DILocation(line: 479, column: 3, scope: !644)
!663 = !DILocation(line: 480, column: 38, scope: !644)
!664 = !DILocation(line: 480, column: 41, scope: !644)
!665 = !DILocation(line: 480, column: 47, scope: !644)
!666 = !DILocation(line: 480, column: 9, scope: !644)
!667 = !DILocation(line: 480, column: 7, scope: !644)
!668 = !DILocation(line: 481, column: 22, scope: !644)
!669 = !DILocation(line: 481, column: 3, scope: !644)
!670 = !DILocation(line: 482, column: 7, scope: !671)
!671 = distinct !DILexicalBlock(scope: !644, file: !1, line: 482, column: 7)
!672 = !DILocation(line: 482, column: 11, scope: !671)
!673 = !DILocation(line: 482, column: 7, scope: !644)
!674 = !DILocation(line: 483, column: 4, scope: !671)
!675 = !DILocation(line: 484, column: 32, scope: !644)
!676 = !DILocation(line: 484, column: 35, scope: !644)
!677 = !DILocation(line: 484, column: 9, scope: !644)
!678 = !DILocation(line: 484, column: 7, scope: !644)
!679 = !DILocation(line: 485, column: 7, scope: !680)
!680 = distinct !DILexicalBlock(scope: !644, file: !1, line: 485, column: 7)
!681 = !DILocation(line: 485, column: 11, scope: !680)
!682 = !DILocation(line: 485, column: 7, scope: !644)
!683 = !DILocation(line: 486, column: 4, scope: !680)
!684 = !DILocation(line: 488, column: 32, scope: !644)
!685 = !DILocation(line: 488, column: 35, scope: !644)
!686 = !DILocation(line: 488, column: 43, scope: !644)
!687 = !DILocation(line: 488, column: 53, scope: !644)
!688 = !DILocation(line: 488, column: 9, scope: !644)
!689 = !DILocation(line: 488, column: 7, scope: !644)
!690 = !DILocation(line: 489, column: 7, scope: !691)
!691 = distinct !DILexicalBlock(scope: !644, file: !1, line: 489, column: 7)
!692 = !DILocation(line: 489, column: 11, scope: !691)
!693 = !DILocation(line: 489, column: 7, scope: !644)
!694 = !DILocation(line: 490, column: 4, scope: !691)
!695 = !DILocation(line: 492, column: 31, scope: !644)
!696 = !DILocation(line: 492, column: 53, scope: !644)
!697 = !DILocation(line: 492, column: 43, scope: !644)
!698 = !DILocation(line: 492, column: 40, scope: !644)
!699 = !DILocation(line: 492, column: 9, scope: !644)
!700 = !DILocation(line: 492, column: 7, scope: !644)
!701 = !DILocation(line: 493, column: 7, scope: !702)
!702 = distinct !DILexicalBlock(scope: !644, file: !1, line: 493, column: 7)
!703 = !DILocation(line: 493, column: 11, scope: !702)
!704 = !DILocation(line: 493, column: 7, scope: !644)
!705 = !DILocation(line: 494, column: 4, scope: !702)
!706 = !DILocation(line: 495, column: 2, scope: !644)
!707 = !DILocation(line: 498, column: 6, scope: !708)
!708 = distinct !DILexicalBlock(scope: !220, file: !1, line: 498, column: 6)
!709 = !DILocation(line: 498, column: 14, scope: !708)
!710 = !DILocation(line: 498, column: 30, scope: !708)
!711 = !DILocation(line: 498, column: 6, scope: !220)
!712 = !DILocalVariable(name: "pathname", scope: !713, file: !1, line: 499, type: !80)
!713 = distinct !DILexicalBlock(scope: !708, file: !1, line: 498, column: 50)
!714 = !DILocation(line: 499, column: 15, scope: !713)
!715 = !DILocation(line: 499, column: 26, scope: !713)
!716 = !DILocation(line: 499, column: 34, scope: !713)
!717 = !DILocalVariable(name: "length", scope: !713, file: !1, line: 500, type: !45)
!718 = !DILocation(line: 500, column: 10, scope: !713)
!719 = !DILocation(line: 500, column: 19, scope: !713)
!720 = !DILocation(line: 500, column: 27, scope: !713)
!721 = !DILocation(line: 500, column: 43, scope: !713)
!722 = !DILocalVariable(name: "temp", scope: !713, file: !1, line: 501, type: !30)
!723 = !DILocation(line: 501, column: 25, scope: !713)
!724 = !DILocation(line: 501, column: 52, scope: !713)
!725 = !DILocation(line: 501, column: 55, scope: !713)
!726 = !DILocation(line: 501, column: 32, scope: !713)
!727 = !DILocation(line: 505, column: 27, scope: !713)
!728 = !DILocation(line: 505, column: 3, scope: !713)
!729 = !DILocation(line: 506, column: 27, scope: !713)
!730 = !DILocation(line: 506, column: 3, scope: !713)
!731 = !DILocation(line: 508, column: 30, scope: !713)
!732 = !DILocation(line: 508, column: 3, scope: !713)
!733 = !DILocation(line: 509, column: 26, scope: !713)
!734 = !DILocation(line: 509, column: 32, scope: !713)
!735 = !DILocation(line: 509, column: 3, scope: !713)
!736 = !DILocation(line: 510, column: 38, scope: !713)
!737 = !DILocation(line: 510, column: 41, scope: !713)
!738 = !DILocation(line: 510, column: 47, scope: !713)
!739 = !DILocation(line: 510, column: 9, scope: !713)
!740 = !DILocation(line: 510, column: 7, scope: !713)
!741 = !DILocation(line: 511, column: 22, scope: !713)
!742 = !DILocation(line: 511, column: 3, scope: !713)
!743 = !DILocation(line: 512, column: 7, scope: !744)
!744 = distinct !DILexicalBlock(scope: !713, file: !1, line: 512, column: 7)
!745 = !DILocation(line: 512, column: 11, scope: !744)
!746 = !DILocation(line: 512, column: 7, scope: !713)
!747 = !DILocation(line: 513, column: 4, scope: !744)
!748 = !DILocation(line: 514, column: 32, scope: !713)
!749 = !DILocation(line: 514, column: 35, scope: !713)
!750 = !DILocation(line: 514, column: 9, scope: !713)
!751 = !DILocation(line: 514, column: 7, scope: !713)
!752 = !DILocation(line: 515, column: 6, scope: !753)
!753 = distinct !DILexicalBlock(scope: !713, file: !1, line: 515, column: 6)
!754 = !DILocation(line: 515, column: 10, scope: !753)
!755 = !DILocation(line: 515, column: 6, scope: !713)
!756 = !DILocation(line: 516, column: 4, scope: !753)
!757 = !DILocation(line: 518, column: 32, scope: !713)
!758 = !DILocation(line: 518, column: 35, scope: !713)
!759 = !DILocation(line: 518, column: 45, scope: !713)
!760 = !DILocation(line: 518, column: 9, scope: !713)
!761 = !DILocation(line: 518, column: 7, scope: !713)
!762 = !DILocation(line: 519, column: 6, scope: !763)
!763 = distinct !DILexicalBlock(scope: !713, file: !1, line: 519, column: 6)
!764 = !DILocation(line: 519, column: 10, scope: !763)
!765 = !DILocation(line: 519, column: 6, scope: !713)
!766 = !DILocation(line: 520, column: 4, scope: !763)
!767 = !DILocation(line: 522, column: 31, scope: !713)
!768 = !DILocation(line: 522, column: 53, scope: !713)
!769 = !DILocation(line: 522, column: 43, scope: !713)
!770 = !DILocation(line: 522, column: 40, scope: !713)
!771 = !DILocation(line: 522, column: 9, scope: !713)
!772 = !DILocation(line: 522, column: 7, scope: !713)
!773 = !DILocation(line: 523, column: 7, scope: !774)
!774 = distinct !DILexicalBlock(scope: !713, file: !1, line: 523, column: 7)
!775 = !DILocation(line: 523, column: 11, scope: !774)
!776 = !DILocation(line: 523, column: 7, scope: !713)
!777 = !DILocation(line: 524, column: 4, scope: !774)
!778 = !DILocation(line: 525, column: 2, scope: !713)
!779 = !DILocation(line: 527, column: 29, scope: !780)
!780 = distinct !DILexicalBlock(scope: !220, file: !1, line: 527, column: 6)
!781 = !DILocation(line: 527, column: 6, scope: !780)
!782 = !DILocation(line: 527, column: 36, scope: !780)
!783 = !DILocation(line: 527, column: 6, scope: !220)
!784 = !DILocation(line: 528, column: 11, scope: !785)
!785 = distinct !DILexicalBlock(scope: !780, file: !1, line: 527, column: 45)
!786 = !DILocation(line: 529, column: 2, scope: !785)
!787 = !DILocation(line: 530, column: 34, scope: !780)
!788 = !DILocation(line: 530, column: 11, scope: !780)
!789 = !DILocation(line: 530, column: 3, scope: !780)
!790 = !DILocation(line: 531, column: 26, scope: !791)
!791 = distinct !DILexicalBlock(scope: !780, file: !1, line: 530, column: 42)
!792 = !DILocation(line: 531, column: 34, scope: !791)
!793 = !DILocation(line: 532, column: 26, scope: !791)
!794 = !DILocation(line: 532, column: 34, scope: !791)
!795 = !DILocation(line: 533, column: 26, scope: !791)
!796 = !DILocation(line: 533, column: 34, scope: !791)
!797 = !DILocation(line: 534, column: 26, scope: !791)
!798 = !DILocation(line: 534, column: 34, scope: !791)
!799 = !DILocation(line: 535, column: 26, scope: !791)
!800 = !DILocation(line: 535, column: 34, scope: !791)
!801 = !DILocation(line: 536, column: 26, scope: !791)
!802 = !DILocation(line: 536, column: 34, scope: !791)
!803 = !DILocation(line: 538, column: 23, scope: !791)
!804 = !DILocation(line: 538, column: 26, scope: !791)
!805 = !DILocation(line: 538, column: 4, scope: !791)
!806 = !DILocation(line: 541, column: 8, scope: !791)
!807 = !DILocation(line: 542, column: 4, scope: !791)
!808 = !DILocation(line: 544, column: 23, scope: !791)
!809 = !DILocation(line: 544, column: 26, scope: !791)
!810 = !DILocation(line: 547, column: 42, scope: !791)
!811 = !DILocation(line: 547, column: 23, scope: !791)
!812 = !DILocation(line: 547, column: 8, scope: !791)
!813 = !DILocation(line: 544, column: 4, scope: !791)
!814 = !DILocation(line: 548, column: 8, scope: !791)
!815 = !DILocation(line: 549, column: 4, scope: !791)
!816 = !DILocation(line: 552, column: 37, scope: !220)
!817 = !DILocation(line: 552, column: 40, scope: !220)
!818 = !DILocation(line: 552, column: 46, scope: !220)
!819 = !DILocation(line: 552, column: 53, scope: !220)
!820 = !DILocation(line: 552, column: 8, scope: !220)
!821 = !DILocation(line: 552, column: 6, scope: !220)
!822 = !DILocation(line: 553, column: 6, scope: !823)
!823 = distinct !DILexicalBlock(scope: !220, file: !1, line: 553, column: 6)
!824 = !DILocation(line: 553, column: 10, scope: !823)
!825 = !DILocation(line: 553, column: 6, scope: !220)
!826 = !DILocation(line: 554, column: 3, scope: !823)
!827 = !DILocation(line: 555, column: 6, scope: !828)
!828 = distinct !DILexicalBlock(scope: !220, file: !1, line: 555, column: 6)
!829 = !DILocation(line: 555, column: 13, scope: !828)
!830 = !DILocation(line: 555, column: 11, scope: !828)
!831 = !DILocation(line: 555, column: 6, scope: !220)
!832 = !DILocation(line: 556, column: 9, scope: !828)
!833 = !DILocation(line: 556, column: 7, scope: !828)
!834 = !DILocation(line: 556, column: 3, scope: !828)
!835 = !DILocation(line: 557, column: 32, scope: !220)
!836 = !DILocation(line: 557, column: 35, scope: !220)
!837 = !DILocation(line: 557, column: 9, scope: !220)
!838 = !DILocation(line: 557, column: 7, scope: !220)
!839 = !DILocation(line: 558, column: 6, scope: !840)
!840 = distinct !DILexicalBlock(scope: !220, file: !1, line: 558, column: 6)
!841 = !DILocation(line: 558, column: 11, scope: !840)
!842 = !DILocation(line: 558, column: 6, scope: !220)
!843 = !DILocation(line: 559, column: 9, scope: !844)
!844 = distinct !DILexicalBlock(scope: !840, file: !1, line: 558, column: 27)
!845 = !DILocation(line: 559, column: 7, scope: !844)
!846 = !DILocation(line: 560, column: 3, scope: !844)
!847 = !DILocation(line: 562, column: 6, scope: !848)
!848 = distinct !DILexicalBlock(scope: !220, file: !1, line: 562, column: 6)
!849 = !DILocation(line: 562, column: 13, scope: !848)
!850 = !DILocation(line: 562, column: 11, scope: !848)
!851 = !DILocation(line: 562, column: 6, scope: !220)
!852 = !DILocation(line: 563, column: 9, scope: !848)
!853 = !DILocation(line: 563, column: 7, scope: !848)
!854 = !DILocation(line: 563, column: 3, scope: !848)
!855 = !DILocation(line: 565, column: 53, scope: !220)
!856 = !DILocation(line: 565, column: 34, scope: !220)
!857 = !DILocation(line: 565, column: 2, scope: !220)
!858 = !DILocation(line: 565, column: 10, scope: !220)
!859 = !DILocation(line: 565, column: 32, scope: !220)
!860 = !DILocation(line: 566, column: 45, scope: !220)
!861 = !DILocation(line: 566, column: 53, scope: !220)
!862 = !DILocation(line: 566, column: 35, scope: !220)
!863 = !DILocation(line: 566, column: 32, scope: !220)
!864 = !DILocation(line: 566, column: 2, scope: !220)
!865 = !DILocation(line: 566, column: 10, scope: !220)
!866 = !DILocation(line: 566, column: 24, scope: !220)
!867 = !DILocation(line: 568, column: 6, scope: !868)
!868 = distinct !DILexicalBlock(scope: !220, file: !1, line: 568, column: 6)
!869 = !DILocation(line: 568, column: 6, scope: !220)
!870 = !DILocation(line: 569, column: 22, scope: !868)
!871 = !DILocation(line: 569, column: 3, scope: !868)
!872 = !DILocation(line: 570, column: 10, scope: !220)
!873 = !DILocation(line: 570, column: 2, scope: !220)
!874 = !DILocation(line: 571, column: 1, scope: !220)
!875 = !DILocalVariable(name: "a", arg: 1, scope: !219, file: !1, line: 257, type: !4)
!876 = !DILocation(line: 257, column: 49, scope: !219)
!877 = !DILocalVariable(name: "buff", arg: 2, scope: !219, file: !1, line: 257, type: !43)
!878 = !DILocation(line: 257, column: 64, scope: !219)
!879 = !DILocalVariable(name: "s", arg: 3, scope: !219, file: !1, line: 257, type: !45)
!880 = !DILocation(line: 257, column: 77, scope: !219)
!881 = !DILocalVariable(name: "gnutar", scope: !219, file: !1, line: 259, type: !192)
!882 = !DILocation(line: 259, column: 17, scope: !219)
!883 = !DILocalVariable(name: "ret", scope: !219, file: !1, line: 260, type: !23)
!884 = !DILocation(line: 260, column: 6, scope: !219)
!885 = !DILocation(line: 262, column: 28, scope: !219)
!886 = !DILocation(line: 262, column: 31, scope: !219)
!887 = !DILocation(line: 262, column: 11, scope: !219)
!888 = !DILocation(line: 262, column: 9, scope: !219)
!889 = !DILocation(line: 263, column: 6, scope: !890)
!890 = distinct !DILexicalBlock(scope: !219, file: !1, line: 263, column: 6)
!891 = !DILocation(line: 263, column: 10, scope: !890)
!892 = !DILocation(line: 263, column: 18, scope: !890)
!893 = !DILocation(line: 263, column: 8, scope: !890)
!894 = !DILocation(line: 263, column: 6, scope: !219)
!895 = !DILocation(line: 264, column: 15, scope: !890)
!896 = !DILocation(line: 264, column: 23, scope: !890)
!897 = !DILocation(line: 264, column: 5, scope: !890)
!898 = !DILocation(line: 264, column: 3, scope: !890)
!899 = !DILocation(line: 265, column: 31, scope: !219)
!900 = !DILocation(line: 265, column: 34, scope: !219)
!901 = !DILocation(line: 265, column: 40, scope: !219)
!902 = !DILocation(line: 265, column: 8, scope: !219)
!903 = !DILocation(line: 265, column: 6, scope: !219)
!904 = !DILocation(line: 266, column: 35, scope: !219)
!905 = !DILocation(line: 266, column: 2, scope: !219)
!906 = !DILocation(line: 266, column: 10, scope: !219)
!907 = !DILocation(line: 266, column: 32, scope: !219)
!908 = !DILocation(line: 267, column: 6, scope: !909)
!909 = distinct !DILexicalBlock(scope: !219, file: !1, line: 267, column: 6)
!910 = !DILocation(line: 267, column: 10, scope: !909)
!911 = !DILocation(line: 267, column: 6, scope: !219)
!912 = !DILocation(line: 268, column: 11, scope: !909)
!913 = !DILocation(line: 268, column: 10, scope: !909)
!914 = !DILocation(line: 268, column: 3, scope: !909)
!915 = !DILocation(line: 269, column: 10, scope: !219)
!916 = !DILocation(line: 269, column: 2, scope: !219)
!917 = !DILocation(line: 270, column: 1, scope: !219)
!918 = !DILocalVariable(name: "a", arg: 1, scope: !216, file: !1, line: 227, type: !4)
!919 = !DILocation(line: 227, column: 50, scope: !216)
!920 = !DILocation(line: 229, column: 32, scope: !216)
!921 = !DILocation(line: 229, column: 10, scope: !216)
!922 = !DILocation(line: 229, column: 2, scope: !216)
!923 = !DILocalVariable(name: "a", arg: 1, scope: !217, file: !1, line: 233, type: !4)
!924 = !DILocation(line: 233, column: 49, scope: !217)
!925 = !DILocalVariable(name: "gnutar", scope: !217, file: !1, line: 235, type: !192)
!926 = !DILocation(line: 235, column: 17, scope: !217)
!927 = !DILocation(line: 237, column: 28, scope: !217)
!928 = !DILocation(line: 237, column: 31, scope: !217)
!929 = !DILocation(line: 237, column: 11, scope: !217)
!930 = !DILocation(line: 237, column: 9, scope: !217)
!931 = !DILocation(line: 238, column: 7, scope: !217)
!932 = !DILocation(line: 238, column: 2, scope: !217)
!933 = !DILocation(line: 239, column: 2, scope: !217)
!934 = !DILocation(line: 239, column: 5, scope: !217)
!935 = !DILocation(line: 239, column: 17, scope: !217)
!936 = !DILocation(line: 240, column: 2, scope: !217)
!937 = !DILocalVariable(name: "a", arg: 1, scope: !218, file: !1, line: 244, type: !4)
!938 = !DILocation(line: 244, column: 57, scope: !218)
!939 = !DILocalVariable(name: "gnutar", scope: !218, file: !1, line: 246, type: !192)
!940 = !DILocation(line: 246, column: 17, scope: !218)
!941 = !DILocalVariable(name: "ret", scope: !218, file: !1, line: 247, type: !23)
!942 = !DILocation(line: 247, column: 6, scope: !218)
!943 = !DILocation(line: 249, column: 28, scope: !218)
!944 = !DILocation(line: 249, column: 31, scope: !218)
!945 = !DILocation(line: 249, column: 11, scope: !218)
!946 = !DILocation(line: 249, column: 9, scope: !218)
!947 = !DILocation(line: 250, column: 30, scope: !218)
!948 = !DILocation(line: 251, column: 7, scope: !218)
!949 = !DILocation(line: 251, column: 15, scope: !218)
!950 = !DILocation(line: 251, column: 39, scope: !218)
!951 = !DILocation(line: 251, column: 47, scope: !218)
!952 = !DILocation(line: 251, column: 37, scope: !218)
!953 = !DILocation(line: 250, column: 8, scope: !218)
!954 = !DILocation(line: 250, column: 6, scope: !218)
!955 = !DILocation(line: 252, column: 34, scope: !218)
!956 = !DILocation(line: 252, column: 42, scope: !218)
!957 = !DILocation(line: 252, column: 56, scope: !218)
!958 = !DILocation(line: 252, column: 2, scope: !218)
!959 = !DILocation(line: 252, column: 10, scope: !218)
!960 = !DILocation(line: 252, column: 32, scope: !218)
!961 = !DILocation(line: 253, column: 10, scope: !218)
!962 = !DILocation(line: 253, column: 2, scope: !218)
!963 = !DILocalVariable(name: "a", arg: 1, scope: !221, file: !1, line: 574, type: !4)
!964 = !DILocation(line: 574, column: 52, scope: !221)
!965 = !DILocalVariable(name: "h", arg: 2, scope: !221, file: !1, line: 574, type: !95)
!966 = !DILocation(line: 574, column: 60, scope: !221)
!967 = !DILocalVariable(name: "entry", arg: 3, scope: !221, file: !1, line: 575, type: !30)
!968 = !DILocation(line: 575, column: 27, scope: !221)
!969 = !DILocalVariable(name: "tartype", arg: 4, scope: !221, file: !1, line: 575, type: !23)
!970 = !DILocation(line: 575, column: 38, scope: !221)
!971 = !DILocalVariable(name: "checksum", scope: !221, file: !1, line: 577, type: !13)
!972 = !DILocation(line: 577, column: 15, scope: !221)
!973 = !DILocalVariable(name: "i", scope: !221, file: !1, line: 578, type: !23)
!974 = !DILocation(line: 578, column: 6, scope: !221)
!975 = !DILocalVariable(name: "ret", scope: !221, file: !1, line: 578, type: !23)
!976 = !DILocation(line: 578, column: 9, scope: !221)
!977 = !DILocalVariable(name: "copy_length", scope: !221, file: !1, line: 579, type: !45)
!978 = !DILocation(line: 579, column: 9, scope: !221)
!979 = !DILocalVariable(name: "p", scope: !221, file: !1, line: 580, type: !80)
!980 = !DILocation(line: 580, column: 14, scope: !221)
!981 = !DILocalVariable(name: "gnutar", scope: !221, file: !1, line: 581, type: !192)
!982 = !DILocation(line: 581, column: 17, scope: !221)
!983 = !DILocation(line: 583, column: 28, scope: !221)
!984 = !DILocation(line: 583, column: 31, scope: !221)
!985 = !DILocation(line: 583, column: 11, scope: !221)
!986 = !DILocation(line: 583, column: 9, scope: !221)
!987 = !DILocation(line: 585, column: 6, scope: !221)
!988 = !DILocation(line: 591, column: 9, scope: !221)
!989 = !DILocation(line: 591, column: 2, scope: !221)
!990 = !DILocation(line: 599, column: 6, scope: !991)
!991 = distinct !DILexicalBlock(scope: !221, file: !1, line: 599, column: 6)
!992 = !DILocation(line: 599, column: 14, scope: !991)
!993 = !DILocation(line: 599, column: 21, scope: !991)
!994 = !DILocation(line: 599, column: 24, scope: !995)
!995 = !DILexicalBlockFile(scope: !991, file: !1, discriminator: 1)
!996 = !DILocation(line: 599, column: 32, scope: !995)
!997 = !DILocation(line: 599, column: 6, scope: !995)
!998 = !DILocation(line: 600, column: 30, scope: !999)
!999 = distinct !DILexicalBlock(scope: !991, file: !1, line: 599, column: 40)
!1000 = !DILocation(line: 600, column: 7, scope: !999)
!1001 = !DILocation(line: 600, column: 5, scope: !999)
!1002 = !DILocation(line: 601, column: 24, scope: !999)
!1003 = !DILocation(line: 601, column: 17, scope: !999)
!1004 = !DILocation(line: 601, column: 15, scope: !999)
!1005 = !DILocation(line: 602, column: 2, scope: !999)
!1006 = !DILocation(line: 603, column: 7, scope: !1007)
!1007 = distinct !DILexicalBlock(scope: !991, file: !1, line: 602, column: 9)
!1008 = !DILocation(line: 603, column: 15, scope: !1007)
!1009 = !DILocation(line: 603, column: 5, scope: !1007)
!1010 = !DILocation(line: 604, column: 17, scope: !1007)
!1011 = !DILocation(line: 604, column: 25, scope: !1007)
!1012 = !DILocation(line: 604, column: 15, scope: !1007)
!1013 = !DILocation(line: 606, column: 6, scope: !1014)
!1014 = distinct !DILexicalBlock(scope: !221, file: !1, line: 606, column: 6)
!1015 = !DILocation(line: 606, column: 18, scope: !1014)
!1016 = !DILocation(line: 606, column: 6, scope: !221)
!1017 = !DILocation(line: 607, column: 15, scope: !1014)
!1018 = !DILocation(line: 607, column: 3, scope: !1014)
!1019 = !DILocation(line: 608, column: 9, scope: !221)
!1020 = !DILocation(line: 608, column: 11, scope: !221)
!1021 = !DILocation(line: 608, column: 33, scope: !221)
!1022 = !DILocation(line: 608, column: 36, scope: !221)
!1023 = !DILocation(line: 608, column: 2, scope: !221)
!1024 = !DILocation(line: 610, column: 21, scope: !1025)
!1025 = distinct !DILexicalBlock(scope: !221, file: !1, line: 610, column: 6)
!1026 = !DILocation(line: 610, column: 29, scope: !1025)
!1027 = !DILocation(line: 610, column: 19, scope: !1025)
!1028 = !DILocation(line: 610, column: 46, scope: !1025)
!1029 = !DILocation(line: 610, column: 6, scope: !221)
!1030 = !DILocation(line: 611, column: 7, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !1032, file: !1, line: 611, column: 7)
!1032 = distinct !DILexicalBlock(scope: !1025, file: !1, line: 610, column: 51)
!1033 = !DILocation(line: 611, column: 19, scope: !1031)
!1034 = !DILocation(line: 611, column: 7, scope: !1032)
!1035 = !DILocation(line: 612, column: 16, scope: !1031)
!1036 = !DILocation(line: 612, column: 4, scope: !1031)
!1037 = !DILocation(line: 613, column: 10, scope: !1032)
!1038 = !DILocation(line: 613, column: 12, scope: !1032)
!1039 = !DILocation(line: 613, column: 38, scope: !1032)
!1040 = !DILocation(line: 613, column: 46, scope: !1032)
!1041 = !DILocation(line: 614, column: 7, scope: !1032)
!1042 = !DILocation(line: 613, column: 3, scope: !1032)
!1043 = !DILocation(line: 615, column: 2, scope: !1032)
!1044 = !DILocation(line: 618, column: 6, scope: !1045)
!1045 = distinct !DILexicalBlock(scope: !221, file: !1, line: 618, column: 6)
!1046 = !DILocation(line: 618, column: 14, scope: !1045)
!1047 = !DILocation(line: 618, column: 21, scope: !1045)
!1048 = !DILocation(line: 618, column: 24, scope: !1049)
!1049 = !DILexicalBlockFile(scope: !1045, file: !1, discriminator: 1)
!1050 = !DILocation(line: 618, column: 32, scope: !1049)
!1051 = !DILocation(line: 618, column: 6, scope: !1049)
!1052 = !DILocation(line: 619, column: 27, scope: !1053)
!1053 = distinct !DILexicalBlock(scope: !1045, file: !1, line: 618, column: 40)
!1054 = !DILocation(line: 619, column: 7, scope: !1053)
!1055 = !DILocation(line: 619, column: 5, scope: !1053)
!1056 = !DILocation(line: 620, column: 24, scope: !1053)
!1057 = !DILocation(line: 620, column: 17, scope: !1053)
!1058 = !DILocation(line: 620, column: 15, scope: !1053)
!1059 = !DILocation(line: 621, column: 2, scope: !1053)
!1060 = !DILocation(line: 622, column: 7, scope: !1061)
!1061 = distinct !DILexicalBlock(scope: !1045, file: !1, line: 621, column: 9)
!1062 = !DILocation(line: 622, column: 15, scope: !1061)
!1063 = !DILocation(line: 622, column: 5, scope: !1061)
!1064 = !DILocation(line: 623, column: 17, scope: !1061)
!1065 = !DILocation(line: 623, column: 25, scope: !1061)
!1066 = !DILocation(line: 623, column: 15, scope: !1061)
!1067 = !DILocation(line: 625, column: 6, scope: !1068)
!1068 = distinct !DILexicalBlock(scope: !221, file: !1, line: 625, column: 6)
!1069 = !DILocation(line: 625, column: 18, scope: !1068)
!1070 = !DILocation(line: 625, column: 6, scope: !221)
!1071 = !DILocation(line: 626, column: 7, scope: !1072)
!1072 = distinct !DILexicalBlock(scope: !1073, file: !1, line: 626, column: 7)
!1073 = distinct !DILexicalBlock(scope: !1068, file: !1, line: 625, column: 23)
!1074 = !DILocation(line: 626, column: 19, scope: !1072)
!1075 = !DILocation(line: 626, column: 7, scope: !1073)
!1076 = !DILocation(line: 627, column: 16, scope: !1072)
!1077 = !DILocation(line: 627, column: 4, scope: !1072)
!1078 = !DILocation(line: 628, column: 10, scope: !1073)
!1079 = !DILocation(line: 628, column: 12, scope: !1073)
!1080 = !DILocation(line: 628, column: 35, scope: !1073)
!1081 = !DILocation(line: 628, column: 38, scope: !1073)
!1082 = !DILocation(line: 628, column: 3, scope: !1073)
!1083 = !DILocation(line: 629, column: 2, scope: !1073)
!1084 = !DILocation(line: 632, column: 6, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !221, file: !1, line: 632, column: 6)
!1086 = !DILocation(line: 632, column: 14, scope: !1085)
!1087 = !DILocation(line: 632, column: 21, scope: !1085)
!1088 = !DILocation(line: 632, column: 24, scope: !1089)
!1089 = !DILexicalBlockFile(scope: !1085, file: !1, discriminator: 1)
!1090 = !DILocation(line: 632, column: 32, scope: !1089)
!1091 = !DILocation(line: 632, column: 6, scope: !1089)
!1092 = !DILocation(line: 633, column: 27, scope: !1093)
!1093 = distinct !DILexicalBlock(scope: !1085, file: !1, line: 632, column: 40)
!1094 = !DILocation(line: 633, column: 7, scope: !1093)
!1095 = !DILocation(line: 633, column: 5, scope: !1093)
!1096 = !DILocation(line: 634, column: 24, scope: !1093)
!1097 = !DILocation(line: 634, column: 17, scope: !1093)
!1098 = !DILocation(line: 634, column: 15, scope: !1093)
!1099 = !DILocation(line: 635, column: 2, scope: !1093)
!1100 = !DILocation(line: 636, column: 7, scope: !1101)
!1101 = distinct !DILexicalBlock(scope: !1085, file: !1, line: 635, column: 9)
!1102 = !DILocation(line: 636, column: 15, scope: !1101)
!1103 = !DILocation(line: 636, column: 5, scope: !1101)
!1104 = !DILocation(line: 637, column: 17, scope: !1101)
!1105 = !DILocation(line: 637, column: 25, scope: !1101)
!1106 = !DILocation(line: 637, column: 15, scope: !1101)
!1107 = !DILocation(line: 639, column: 6, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !221, file: !1, line: 639, column: 6)
!1109 = !DILocation(line: 639, column: 18, scope: !1108)
!1110 = !DILocation(line: 639, column: 6, scope: !221)
!1111 = !DILocation(line: 640, column: 14, scope: !1112)
!1112 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 640, column: 7)
!1113 = distinct !DILexicalBlock(scope: !1108, file: !1, line: 639, column: 23)
!1114 = !DILocation(line: 640, column: 7, scope: !1112)
!1115 = !DILocation(line: 640, column: 17, scope: !1112)
!1116 = !DILocation(line: 640, column: 7, scope: !1113)
!1117 = !DILocation(line: 641, column: 16, scope: !1112)
!1118 = !DILocation(line: 641, column: 4, scope: !1112)
!1119 = !DILocation(line: 642, column: 10, scope: !1113)
!1120 = !DILocation(line: 642, column: 12, scope: !1113)
!1121 = !DILocation(line: 642, column: 35, scope: !1113)
!1122 = !DILocation(line: 642, column: 38, scope: !1113)
!1123 = !DILocation(line: 642, column: 3, scope: !1113)
!1124 = !DILocation(line: 643, column: 2, scope: !1113)
!1125 = !DILocation(line: 646, column: 34, scope: !221)
!1126 = !DILocation(line: 646, column: 15, scope: !221)
!1127 = !DILocation(line: 646, column: 41, scope: !221)
!1128 = !DILocation(line: 647, column: 6, scope: !221)
!1129 = !DILocation(line: 647, column: 8, scope: !221)
!1130 = !DILocation(line: 646, column: 2, scope: !1131)
!1131 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 1)
!1132 = !DILocation(line: 650, column: 38, scope: !1133)
!1133 = distinct !DILexicalBlock(scope: !221, file: !1, line: 650, column: 6)
!1134 = !DILocation(line: 650, column: 20, scope: !1133)
!1135 = !DILocation(line: 650, column: 46, scope: !1133)
!1136 = !DILocation(line: 650, column: 48, scope: !1133)
!1137 = !DILocation(line: 650, column: 6, scope: !1138)
!1138 = !DILexicalBlockFile(scope: !1133, file: !1, discriminator: 1)
!1139 = !DILocation(line: 650, column: 6, scope: !1133)
!1140 = !DILocation(line: 650, column: 6, scope: !221)
!1141 = !DILocation(line: 652, column: 22, scope: !1142)
!1142 = distinct !DILexicalBlock(scope: !1133, file: !1, line: 651, column: 42)
!1143 = !DILocation(line: 652, column: 25, scope: !1142)
!1144 = !DILocation(line: 654, column: 35, scope: !1142)
!1145 = !DILocation(line: 654, column: 17, scope: !1142)
!1146 = !DILocation(line: 652, column: 3, scope: !1142)
!1147 = !DILocation(line: 655, column: 7, scope: !1142)
!1148 = !DILocation(line: 656, column: 2, scope: !1142)
!1149 = !DILocation(line: 659, column: 38, scope: !1150)
!1150 = distinct !DILexicalBlock(scope: !221, file: !1, line: 659, column: 6)
!1151 = !DILocation(line: 659, column: 20, scope: !1150)
!1152 = !DILocation(line: 659, column: 46, scope: !1150)
!1153 = !DILocation(line: 659, column: 48, scope: !1150)
!1154 = !DILocation(line: 659, column: 6, scope: !1155)
!1155 = !DILexicalBlockFile(scope: !1150, file: !1, discriminator: 1)
!1156 = !DILocation(line: 659, column: 6, scope: !1150)
!1157 = !DILocation(line: 659, column: 6, scope: !221)
!1158 = !DILocation(line: 661, column: 22, scope: !1159)
!1159 = distinct !DILexicalBlock(scope: !1150, file: !1, line: 660, column: 42)
!1160 = !DILocation(line: 661, column: 25, scope: !1159)
!1161 = !DILocation(line: 663, column: 35, scope: !1159)
!1162 = !DILocation(line: 663, column: 17, scope: !1159)
!1163 = !DILocation(line: 661, column: 3, scope: !1159)
!1164 = !DILocation(line: 664, column: 7, scope: !1159)
!1165 = !DILocation(line: 665, column: 2, scope: !1159)
!1166 = !DILocation(line: 668, column: 39, scope: !1167)
!1167 = distinct !DILexicalBlock(scope: !221, file: !1, line: 668, column: 6)
!1168 = !DILocation(line: 668, column: 20, scope: !1167)
!1169 = !DILocation(line: 668, column: 47, scope: !1167)
!1170 = !DILocation(line: 668, column: 49, scope: !1167)
!1171 = !DILocation(line: 668, column: 6, scope: !1172)
!1172 = !DILexicalBlockFile(scope: !1167, file: !1, discriminator: 1)
!1173 = !DILocation(line: 668, column: 6, scope: !1167)
!1174 = !DILocation(line: 668, column: 6, scope: !221)
!1175 = !DILocation(line: 670, column: 22, scope: !1176)
!1176 = distinct !DILexicalBlock(scope: !1167, file: !1, line: 669, column: 44)
!1177 = !DILocation(line: 670, column: 25, scope: !1176)
!1178 = !DILocation(line: 670, column: 3, scope: !1176)
!1179 = !DILocation(line: 672, column: 7, scope: !1176)
!1180 = !DILocation(line: 673, column: 2, scope: !1176)
!1181 = !DILocation(line: 676, column: 35, scope: !221)
!1182 = !DILocation(line: 676, column: 15, scope: !221)
!1183 = !DILocation(line: 677, column: 6, scope: !221)
!1184 = !DILocation(line: 677, column: 8, scope: !221)
!1185 = !DILocation(line: 676, column: 2, scope: !1131)
!1186 = !DILocation(line: 679, column: 29, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !221, file: !1, line: 679, column: 6)
!1188 = !DILocation(line: 679, column: 6, scope: !1187)
!1189 = !DILocation(line: 679, column: 36, scope: !1187)
!1190 = !DILocation(line: 680, column: 6, scope: !1187)
!1191 = !DILocation(line: 680, column: 32, scope: !1192)
!1192 = !DILexicalBlockFile(scope: !1187, file: !1, discriminator: 1)
!1193 = !DILocation(line: 680, column: 9, scope: !1192)
!1194 = !DILocation(line: 680, column: 39, scope: !1192)
!1195 = !DILocation(line: 679, column: 6, scope: !1131)
!1196 = !DILocation(line: 681, column: 44, scope: !1197)
!1197 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 681, column: 7)
!1198 = distinct !DILexicalBlock(scope: !1187, file: !1, line: 680, column: 52)
!1199 = !DILocation(line: 681, column: 20, scope: !1197)
!1200 = !DILocation(line: 682, column: 7, scope: !1197)
!1201 = !DILocation(line: 682, column: 9, scope: !1197)
!1202 = !DILocation(line: 681, column: 7, scope: !1203)
!1203 = !DILexicalBlockFile(scope: !1197, file: !1, discriminator: 1)
!1204 = !DILocation(line: 681, column: 7, scope: !1197)
!1205 = !DILocation(line: 681, column: 7, scope: !1198)
!1206 = !DILocation(line: 684, column: 23, scope: !1207)
!1207 = distinct !DILexicalBlock(scope: !1197, file: !1, line: 683, column: 28)
!1208 = !DILocation(line: 684, column: 26, scope: !1207)
!1209 = !DILocation(line: 684, column: 4, scope: !1207)
!1210 = !DILocation(line: 686, column: 8, scope: !1207)
!1211 = !DILocation(line: 687, column: 3, scope: !1207)
!1212 = !DILocation(line: 689, column: 44, scope: !1213)
!1213 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 689, column: 7)
!1214 = !DILocation(line: 689, column: 20, scope: !1213)
!1215 = !DILocation(line: 690, column: 7, scope: !1213)
!1216 = !DILocation(line: 690, column: 9, scope: !1213)
!1217 = !DILocation(line: 689, column: 7, scope: !1218)
!1218 = !DILexicalBlockFile(scope: !1213, file: !1, discriminator: 1)
!1219 = !DILocation(line: 689, column: 7, scope: !1213)
!1220 = !DILocation(line: 689, column: 7, scope: !1198)
!1221 = !DILocation(line: 692, column: 23, scope: !1222)
!1222 = distinct !DILexicalBlock(scope: !1213, file: !1, line: 691, column: 28)
!1223 = !DILocation(line: 692, column: 26, scope: !1222)
!1224 = !DILocation(line: 692, column: 4, scope: !1222)
!1225 = !DILocation(line: 694, column: 8, scope: !1222)
!1226 = !DILocation(line: 695, column: 3, scope: !1222)
!1227 = !DILocation(line: 696, column: 2, scope: !1198)
!1228 = !DILocation(line: 698, column: 30, scope: !221)
!1229 = !DILocation(line: 698, column: 2, scope: !221)
!1230 = !DILocation(line: 698, column: 28, scope: !221)
!1231 = !DILocation(line: 700, column: 11, scope: !221)
!1232 = !DILocation(line: 701, column: 9, scope: !1233)
!1233 = distinct !DILexicalBlock(scope: !221, file: !1, line: 701, column: 2)
!1234 = !DILocation(line: 701, column: 7, scope: !1233)
!1235 = !DILocation(line: 701, column: 14, scope: !1236)
!1236 = !DILexicalBlockFile(scope: !1237, file: !1, discriminator: 1)
!1237 = distinct !DILexicalBlock(scope: !1233, file: !1, line: 701, column: 2)
!1238 = !DILocation(line: 701, column: 16, scope: !1236)
!1239 = !DILocation(line: 701, column: 2, scope: !1236)
!1240 = !DILocation(line: 702, column: 37, scope: !1237)
!1241 = !DILocation(line: 702, column: 35, scope: !1237)
!1242 = !DILocation(line: 702, column: 21, scope: !1237)
!1243 = !DILocation(line: 702, column: 19, scope: !1237)
!1244 = !DILocation(line: 702, column: 12, scope: !1237)
!1245 = !DILocation(line: 702, column: 3, scope: !1237)
!1246 = !DILocation(line: 701, column: 24, scope: !1247)
!1247 = !DILexicalBlockFile(scope: !1237, file: !1, discriminator: 2)
!1248 = !DILocation(line: 701, column: 2, scope: !1247)
!1249 = !DILocation(line: 703, column: 2, scope: !221)
!1250 = !DILocation(line: 703, column: 32, scope: !221)
!1251 = !DILocation(line: 705, column: 15, scope: !221)
!1252 = !DILocation(line: 705, column: 25, scope: !221)
!1253 = !DILocation(line: 705, column: 27, scope: !221)
!1254 = !DILocation(line: 705, column: 2, scope: !221)
!1255 = !DILocation(line: 706, column: 10, scope: !221)
!1256 = !DILocation(line: 706, column: 2, scope: !221)
!1257 = !DILocalVariable(name: "v", arg: 1, scope: !224, file: !1, line: 741, type: !52)
!1258 = !DILocation(line: 741, column: 22, scope: !224)
!1259 = !DILocalVariable(name: "p", arg: 2, scope: !224, file: !1, line: 741, type: !95)
!1260 = !DILocation(line: 741, column: 31, scope: !224)
!1261 = !DILocalVariable(name: "s", arg: 3, scope: !224, file: !1, line: 741, type: !23)
!1262 = !DILocation(line: 741, column: 38, scope: !224)
!1263 = !DILocalVariable(name: "len", scope: !224, file: !1, line: 743, type: !23)
!1264 = !DILocation(line: 743, column: 6, scope: !224)
!1265 = !DILocation(line: 743, column: 12, scope: !224)
!1266 = !DILocation(line: 746, column: 6, scope: !1267)
!1267 = distinct !DILexicalBlock(scope: !224, file: !1, line: 746, column: 6)
!1268 = !DILocation(line: 746, column: 8, scope: !1267)
!1269 = !DILocation(line: 746, column: 6, scope: !224)
!1270 = !DILocation(line: 747, column: 5, scope: !1267)
!1271 = !DILocation(line: 747, column: 3, scope: !1267)
!1272 = !DILocation(line: 749, column: 7, scope: !224)
!1273 = !DILocation(line: 749, column: 4, scope: !224)
!1274 = !DILocation(line: 750, column: 2, scope: !224)
!1275 = !DILocation(line: 750, column: 10, scope: !1276)
!1276 = !DILexicalBlockFile(scope: !224, file: !1, discriminator: 1)
!1277 = !DILocation(line: 750, column: 13, scope: !1276)
!1278 = !DILocation(line: 750, column: 2, scope: !1276)
!1279 = !DILocation(line: 751, column: 24, scope: !1280)
!1280 = distinct !DILexicalBlock(scope: !224, file: !1, line: 750, column: 18)
!1281 = !DILocation(line: 751, column: 26, scope: !1280)
!1282 = !DILocation(line: 751, column: 21, scope: !1280)
!1283 = !DILocation(line: 751, column: 10, scope: !1280)
!1284 = !DILocation(line: 751, column: 4, scope: !1280)
!1285 = !DILocation(line: 751, column: 8, scope: !1280)
!1286 = !DILocation(line: 752, column: 5, scope: !1280)
!1287 = !DILocation(line: 750, column: 2, scope: !1288)
!1288 = !DILexicalBlockFile(scope: !224, file: !1, discriminator: 2)
!1289 = !DILocation(line: 755, column: 6, scope: !1290)
!1290 = distinct !DILexicalBlock(scope: !224, file: !1, line: 755, column: 6)
!1291 = !DILocation(line: 755, column: 8, scope: !1290)
!1292 = !DILocation(line: 755, column: 6, scope: !224)
!1293 = !DILocation(line: 756, column: 3, scope: !1290)
!1294 = !DILocation(line: 759, column: 2, scope: !224)
!1295 = !DILocation(line: 759, column: 12, scope: !1276)
!1296 = !DILocation(line: 759, column: 15, scope: !1276)
!1297 = !DILocation(line: 759, column: 2, scope: !1276)
!1298 = !DILocation(line: 760, column: 5, scope: !224)
!1299 = !DILocation(line: 760, column: 8, scope: !224)
!1300 = !DILocation(line: 759, column: 2, scope: !1288)
!1301 = !DILocation(line: 762, column: 2, scope: !224)
!1302 = !DILocation(line: 763, column: 1, scope: !224)
!1303 = !DILocalVariable(name: "v", arg: 1, scope: !227, file: !1, line: 713, type: !52)
!1304 = !DILocation(line: 713, column: 23, scope: !227)
!1305 = !DILocalVariable(name: "p", arg: 2, scope: !227, file: !1, line: 713, type: !95)
!1306 = !DILocation(line: 713, column: 32, scope: !227)
!1307 = !DILocalVariable(name: "s", arg: 3, scope: !227, file: !1, line: 713, type: !23)
!1308 = !DILocation(line: 713, column: 39, scope: !227)
!1309 = !DILocalVariable(name: "maxsize", arg: 4, scope: !227, file: !1, line: 713, type: !23)
!1310 = !DILocation(line: 713, column: 46, scope: !227)
!1311 = !DILocalVariable(name: "limit", scope: !227, file: !1, line: 715, type: !52)
!1312 = !DILocation(line: 715, column: 10, scope: !227)
!1313 = !DILocation(line: 715, column: 34, scope: !227)
!1314 = !DILocation(line: 715, column: 35, scope: !227)
!1315 = !DILocation(line: 715, column: 30, scope: !227)
!1316 = !DILocation(line: 717, column: 6, scope: !1317)
!1317 = distinct !DILexicalBlock(scope: !227, file: !1, line: 717, column: 6)
!1318 = !DILocation(line: 717, column: 10, scope: !1317)
!1319 = !DILocation(line: 717, column: 8, scope: !1317)
!1320 = !DILocation(line: 717, column: 6, scope: !227)
!1321 = !DILocation(line: 718, column: 24, scope: !1317)
!1322 = !DILocation(line: 718, column: 27, scope: !1317)
!1323 = !DILocation(line: 718, column: 30, scope: !1317)
!1324 = !DILocation(line: 718, column: 11, scope: !1317)
!1325 = !DILocation(line: 718, column: 3, scope: !1317)
!1326 = !DILocation(line: 719, column: 21, scope: !227)
!1327 = !DILocation(line: 719, column: 24, scope: !227)
!1328 = !DILocation(line: 719, column: 27, scope: !227)
!1329 = !DILocation(line: 719, column: 10, scope: !227)
!1330 = !DILocation(line: 719, column: 2, scope: !227)
!1331 = !DILocation(line: 720, column: 1, scope: !227)
!1332 = !DILocalVariable(name: "v", arg: 1, scope: !230, file: !1, line: 726, type: !52)
!1333 = !DILocation(line: 726, column: 20, scope: !230)
!1334 = !DILocalVariable(name: "p", arg: 2, scope: !230, file: !1, line: 726, type: !95)
!1335 = !DILocation(line: 726, column: 29, scope: !230)
!1336 = !DILocalVariable(name: "s", arg: 3, scope: !230, file: !1, line: 726, type: !23)
!1337 = !DILocation(line: 726, column: 36, scope: !230)
!1338 = !DILocation(line: 728, column: 7, scope: !230)
!1339 = !DILocation(line: 728, column: 4, scope: !230)
!1340 = !DILocation(line: 729, column: 2, scope: !230)
!1341 = !DILocation(line: 729, column: 10, scope: !1342)
!1342 = !DILexicalBlockFile(scope: !230, file: !1, discriminator: 1)
!1343 = !DILocation(line: 729, column: 13, scope: !1342)
!1344 = !DILocation(line: 729, column: 2, scope: !1342)
!1345 = !DILocation(line: 730, column: 17, scope: !1346)
!1346 = distinct !DILexicalBlock(scope: !230, file: !1, line: 729, column: 18)
!1347 = !DILocation(line: 730, column: 19, scope: !1346)
!1348 = !DILocation(line: 730, column: 10, scope: !1346)
!1349 = !DILocation(line: 730, column: 4, scope: !1346)
!1350 = !DILocation(line: 730, column: 8, scope: !1346)
!1351 = !DILocation(line: 731, column: 5, scope: !1346)
!1352 = !DILocation(line: 729, column: 2, scope: !1353)
!1353 = !DILexicalBlockFile(scope: !230, file: !1, discriminator: 2)
!1354 = !DILocation(line: 733, column: 3, scope: !230)
!1355 = !DILocation(line: 733, column: 5, scope: !230)
!1356 = !DILocation(line: 734, column: 2, scope: !230)
