; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_pack_dev.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.format = type { i8*, i64 (i32, i64*, i8**)* }

@iMajorError = internal constant [21 x i8] c"invalid major number\00", align 16
@iMinorError = internal constant [21 x i8] c"invalid minor number\00", align 16
@tooManyFields = internal constant [27 x i8] c"too many fields for format\00", align 16
@formats = internal global [16 x %struct.format] [%struct.format { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }, %struct.format { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }, %struct.format { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_bsdos }, %struct.format { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.3, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_freebsd }, %struct.format { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_24 }, %struct.format { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }, %struct.format { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }, %struct.format { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_native }, %struct.format { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.8, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_netbsd }, %struct.format { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_12_20 }, %struct.format { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }, %struct.format { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.11, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_14_18 }, %struct.format { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }, %struct.format { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }, %struct.format { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.14, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_14_18 }, %struct.format { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.15, i32 0, i32 0), i64 (i32, i64*, i8**)* @pack_8_8 }], align 16
@.str = private unnamed_addr constant [7 x i8] c"386bsd\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"4bsd\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"bsdos\00", align 1
@.str.3 = private unnamed_addr constant [8 x i8] c"freebsd\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"hpux\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"isc\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"linux\00", align 1
@.str.7 = private unnamed_addr constant [7 x i8] c"native\00", align 1
@.str.8 = private unnamed_addr constant [7 x i8] c"netbsd\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c"osf1\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"sco\00", align 1
@.str.11 = private unnamed_addr constant [8 x i8] c"solaris\00", align 1
@.str.12 = private unnamed_addr constant [6 x i8] c"sunos\00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c"svr3\00", align 1
@.str.14 = private unnamed_addr constant [5 x i8] c"svr4\00", align 1
@.str.15 = private unnamed_addr constant [7 x i8] c"ultrix\00", align 1
@.str.16 = private unnamed_addr constant [20 x i8] c"invalid unit number\00", align 1
@.str.17 = private unnamed_addr constant [23 x i8] c"invalid subunit number\00", align 1

; Function Attrs: nounwind uwtable
define i64 @pack_native(i32 %n, i64* %numbers, i8** %error) #0 !dbg !13 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !60, metadata !61), !dbg !62
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !63, metadata !61), !dbg !64
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !65, metadata !61), !dbg !66
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !67, metadata !61), !dbg !68
  store i64 0, i64* %dev, align 8, !dbg !68
  %0 = load i32, i32* %n.addr, align 4, !dbg !69
  %cmp = icmp eq i32 %0, 2, !dbg !71
  br i1 %cmp, label %if.then, label %if.else16, !dbg !72

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !73
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !73
  %2 = load i64, i64* %arrayidx, align 8, !dbg !73
  %conv = trunc i64 %2 to i32, !dbg !73
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !73
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !73
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !73
  %conv2 = trunc i64 %4 to i32, !dbg !73
  %call = call i64 @gnu_dev_makedev(i32 %conv, i32 %conv2) #1, !dbg !73
  store i64 %call, i64* %dev, align 8, !dbg !75
  %5 = load i64, i64* %dev, align 8, !dbg !76
  %call3 = call i32 @gnu_dev_major(i64 %5) #1, !dbg !76
  %conv4 = zext i32 %call3 to i64, !dbg !78
  %6 = load i64*, i64** %numbers.addr, align 8, !dbg !79
  %arrayidx5 = getelementptr inbounds i64, i64* %6, i64 0, !dbg !79
  %7 = load i64, i64* %arrayidx5, align 8, !dbg !79
  %cmp6 = icmp ne i64 %conv4, %7, !dbg !80
  br i1 %cmp6, label %if.then8, label %if.else, !dbg !81

if.then8:                                         ; preds = %if.then
  %8 = load i8**, i8*** %error.addr, align 8, !dbg !82
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %8, align 8, !dbg !83
  br label %if.end15, !dbg !84

if.else:                                          ; preds = %if.then
  %9 = load i64, i64* %dev, align 8, !dbg !85
  %call9 = call i32 @gnu_dev_minor(i64 %9) #1, !dbg !85
  %conv10 = zext i32 %call9 to i64, !dbg !87
  %10 = load i64*, i64** %numbers.addr, align 8, !dbg !88
  %arrayidx11 = getelementptr inbounds i64, i64* %10, i64 1, !dbg !88
  %11 = load i64, i64* %arrayidx11, align 8, !dbg !88
  %cmp12 = icmp ne i64 %conv10, %11, !dbg !89
  br i1 %cmp12, label %if.then14, label %if.end, !dbg !90

if.then14:                                        ; preds = %if.else
  %12 = load i8**, i8*** %error.addr, align 8, !dbg !91
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %12, align 8, !dbg !92
  br label %if.end, !dbg !93

if.end:                                           ; preds = %if.then14, %if.else
  br label %if.end15

if.end15:                                         ; preds = %if.end, %if.then8
  br label %if.end17, !dbg !94

if.else16:                                        ; preds = %entry
  %13 = load i8**, i8*** %error.addr, align 8, !dbg !95
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %13, align 8, !dbg !96
  br label %if.end17

if.end17:                                         ; preds = %if.else16, %if.end15
  %14 = load i64, i64* %dev, align 8, !dbg !97
  ret i64 %14, !dbg !98
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readnone
declare i64 @gnu_dev_makedev(i32, i32) #2

; Function Attrs: nounwind readnone
declare i32 @gnu_dev_major(i64) #2

; Function Attrs: nounwind readnone
declare i32 @gnu_dev_minor(i64) #2

; Function Attrs: nounwind uwtable
define i64 (i32, i64*, i8**)* @pack_find(i8* %name) #0 !dbg !21 {
entry:
  %retval = alloca i64 (i32, i64*, i8**)*, align 8
  %name.addr = alloca i8*, align 8
  %format = alloca %struct.format*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !99, metadata !61), !dbg !100
  call void @llvm.dbg.declare(metadata %struct.format** %format, metadata !101, metadata !61), !dbg !103
  %0 = load i8*, i8** %name.addr, align 8, !dbg !104
  %call = call i8* @bsearch(i8* %0, i8* bitcast ([16 x %struct.format]* @formats to i8*), i64 16, i64 16, i32 (i8*, i8*)* @compare_format), !dbg !105
  %1 = bitcast i8* %call to %struct.format*, !dbg !105
  store %struct.format* %1, %struct.format** %format, align 8, !dbg !106
  %2 = load %struct.format*, %struct.format** %format, align 8, !dbg !107
  %cmp = icmp eq %struct.format* %2, null, !dbg !109
  br i1 %cmp, label %if.then, label %if.end, !dbg !110

if.then:                                          ; preds = %entry
  store i64 (i32, i64*, i8**)* null, i64 (i32, i64*, i8**)** %retval, align 8, !dbg !111
  br label %return, !dbg !111

if.end:                                           ; preds = %entry
  %3 = load %struct.format*, %struct.format** %format, align 8, !dbg !112
  %pack = getelementptr inbounds %struct.format, %struct.format* %3, i32 0, i32 1, !dbg !113
  %4 = load i64 (i32, i64*, i8**)*, i64 (i32, i64*, i8**)** %pack, align 8, !dbg !113
  store i64 (i32, i64*, i8**)* %4, i64 (i32, i64*, i8**)** %retval, align 8, !dbg !114
  br label %return, !dbg !114

return:                                           ; preds = %if.end, %if.then
  %5 = load i64 (i32, i64*, i8**)*, i64 (i32, i64*, i8**)** %retval, align 8, !dbg !115
  ret i64 (i32, i64*, i8**)* %5, !dbg !115
}

declare i8* @bsearch(i8*, i8*, i64, i64, i32 (i8*, i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @compare_format(i8* %key, i8* %element) #0 !dbg !34 {
entry:
  %key.addr = alloca i8*, align 8
  %element.addr = alloca i8*, align 8
  %name = alloca i8*, align 8
  %format = alloca %struct.format*, align 8
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !116, metadata !61), !dbg !117
  store i8* %element, i8** %element.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %element.addr, metadata !118, metadata !61), !dbg !119
  call void @llvm.dbg.declare(metadata i8** %name, metadata !120, metadata !61), !dbg !121
  call void @llvm.dbg.declare(metadata %struct.format** %format, metadata !122, metadata !61), !dbg !125
  %0 = load i8*, i8** %key.addr, align 8, !dbg !126
  store i8* %0, i8** %name, align 8, !dbg !127
  %1 = load i8*, i8** %element.addr, align 8, !dbg !128
  %2 = bitcast i8* %1 to %struct.format*, !dbg !128
  store %struct.format* %2, %struct.format** %format, align 8, !dbg !129
  %3 = load i8*, i8** %name, align 8, !dbg !130
  %4 = load %struct.format*, %struct.format** %format, align 8, !dbg !131
  %name1 = getelementptr inbounds %struct.format, %struct.format* %4, i32 0, i32 0, !dbg !132
  %5 = load i8*, i8** %name1, align 8, !dbg !132
  %call = call i32 @strcmp(i8* %3, i8* %5) #5, !dbg !133
  ret i32 %call, !dbg !134
}

; Function Attrs: nounwind uwtable
define internal i64 @pack_8_8(i32 %n, i64* %numbers, i8** %error) #0 !dbg !27 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !135, metadata !61), !dbg !136
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !137, metadata !61), !dbg !138
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !139, metadata !61), !dbg !140
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !141, metadata !61), !dbg !142
  store i64 0, i64* %dev, align 8, !dbg !142
  %0 = load i32, i32* %n.addr, align 4, !dbg !143
  %cmp = icmp eq i32 %0, 2, !dbg !145
  br i1 %cmp, label %if.then, label %if.else, !dbg !146

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !147
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !147
  %2 = load i64, i64* %arrayidx, align 8, !dbg !147
  %shl = shl i64 %2, 8, !dbg !147
  %and = and i64 %shl, 65280, !dbg !147
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !147
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !147
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !147
  %shl2 = shl i64 %4, 0, !dbg !147
  %and3 = and i64 %shl2, 255, !dbg !147
  %or = or i64 %and, %and3, !dbg !147
  store i64 %or, i64* %dev, align 8, !dbg !149
  %5 = load i64, i64* %dev, align 8, !dbg !150
  %and4 = and i64 %5, 65280, !dbg !150
  %shr = lshr i64 %and4, 8, !dbg !150
  %conv = trunc i64 %shr to i32, !dbg !150
  %conv5 = sext i32 %conv to i64, !dbg !152
  %6 = load i64*, i64** %numbers.addr, align 8, !dbg !153
  %arrayidx6 = getelementptr inbounds i64, i64* %6, i64 0, !dbg !153
  %7 = load i64, i64* %arrayidx6, align 8, !dbg !153
  %cmp7 = icmp ne i64 %conv5, %7, !dbg !154
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !155

if.then9:                                         ; preds = %if.then
  %8 = load i8**, i8*** %error.addr, align 8, !dbg !156
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %8, align 8, !dbg !157
  br label %if.end, !dbg !158

if.end:                                           ; preds = %if.then9, %if.then
  %9 = load i64, i64* %dev, align 8, !dbg !159
  %and10 = and i64 %9, 255, !dbg !159
  %shr11 = lshr i64 %and10, 0, !dbg !159
  %conv12 = trunc i64 %shr11 to i32, !dbg !159
  %conv13 = sext i32 %conv12 to i64, !dbg !161
  %10 = load i64*, i64** %numbers.addr, align 8, !dbg !162
  %arrayidx14 = getelementptr inbounds i64, i64* %10, i64 1, !dbg !162
  %11 = load i64, i64* %arrayidx14, align 8, !dbg !162
  %cmp15 = icmp ne i64 %conv13, %11, !dbg !163
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !164

if.then17:                                        ; preds = %if.end
  %12 = load i8**, i8*** %error.addr, align 8, !dbg !165
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %12, align 8, !dbg !166
  br label %if.end18, !dbg !167

if.end18:                                         ; preds = %if.then17, %if.end
  br label %if.end19, !dbg !168

if.else:                                          ; preds = %entry
  %13 = load i8**, i8*** %error.addr, align 8, !dbg !169
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %13, align 8, !dbg !170
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.end18
  %14 = load i64, i64* %dev, align 8, !dbg !171
  ret i64 %14, !dbg !172
}

; Function Attrs: nounwind uwtable
define internal i64 @pack_bsdos(i32 %n, i64* %numbers, i8** %error) #0 !dbg !28 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !173, metadata !61), !dbg !174
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !175, metadata !61), !dbg !176
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !177, metadata !61), !dbg !178
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !179, metadata !61), !dbg !180
  store i64 0, i64* %dev, align 8, !dbg !180
  %0 = load i32, i32* %n.addr, align 4, !dbg !181
  %cmp = icmp eq i32 %0, 2, !dbg !183
  br i1 %cmp, label %if.then, label %if.else, !dbg !184

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !185
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !185
  %2 = load i64, i64* %arrayidx, align 8, !dbg !185
  %shl = shl i64 %2, 20, !dbg !185
  %and = and i64 %shl, 4293918720, !dbg !185
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !185
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !185
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !185
  %shl2 = shl i64 %4, 0, !dbg !185
  %and3 = and i64 %shl2, 1048575, !dbg !185
  %or = or i64 %and, %and3, !dbg !185
  store i64 %or, i64* %dev, align 8, !dbg !187
  %5 = load i64, i64* %dev, align 8, !dbg !188
  %and4 = and i64 %5, 4293918720, !dbg !188
  %shr = lshr i64 %and4, 20, !dbg !188
  %conv = trunc i64 %shr to i32, !dbg !188
  %conv5 = sext i32 %conv to i64, !dbg !190
  %6 = load i64*, i64** %numbers.addr, align 8, !dbg !191
  %arrayidx6 = getelementptr inbounds i64, i64* %6, i64 0, !dbg !191
  %7 = load i64, i64* %arrayidx6, align 8, !dbg !191
  %cmp7 = icmp ne i64 %conv5, %7, !dbg !192
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !193

if.then9:                                         ; preds = %if.then
  %8 = load i8**, i8*** %error.addr, align 8, !dbg !194
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %8, align 8, !dbg !195
  br label %if.end, !dbg !196

if.end:                                           ; preds = %if.then9, %if.then
  %9 = load i64, i64* %dev, align 8, !dbg !197
  %and10 = and i64 %9, 1048575, !dbg !197
  %shr11 = lshr i64 %and10, 0, !dbg !197
  %conv12 = trunc i64 %shr11 to i32, !dbg !197
  %conv13 = sext i32 %conv12 to i64, !dbg !199
  %10 = load i64*, i64** %numbers.addr, align 8, !dbg !200
  %arrayidx14 = getelementptr inbounds i64, i64* %10, i64 1, !dbg !200
  %11 = load i64, i64* %arrayidx14, align 8, !dbg !200
  %cmp15 = icmp ne i64 %conv13, %11, !dbg !201
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !202

if.then17:                                        ; preds = %if.end
  %12 = load i8**, i8*** %error.addr, align 8, !dbg !203
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %12, align 8, !dbg !204
  br label %if.end18, !dbg !205

if.end18:                                         ; preds = %if.then17, %if.end
  br label %if.end62, !dbg !206

if.else:                                          ; preds = %entry
  %13 = load i32, i32* %n.addr, align 4, !dbg !207
  %cmp19 = icmp eq i32 %13, 3, !dbg !210
  br i1 %cmp19, label %if.then21, label %if.else60, !dbg !207

if.then21:                                        ; preds = %if.else
  %14 = load i64*, i64** %numbers.addr, align 8, !dbg !211
  %arrayidx22 = getelementptr inbounds i64, i64* %14, i64 0, !dbg !211
  %15 = load i64, i64* %arrayidx22, align 8, !dbg !211
  %shl23 = shl i64 %15, 20, !dbg !211
  %and24 = and i64 %shl23, 4293918720, !dbg !211
  %16 = load i64*, i64** %numbers.addr, align 8, !dbg !211
  %arrayidx25 = getelementptr inbounds i64, i64* %16, i64 1, !dbg !211
  %17 = load i64, i64* %arrayidx25, align 8, !dbg !211
  %shl26 = shl i64 %17, 8, !dbg !211
  %and27 = and i64 %shl26, 1048320, !dbg !211
  %or28 = or i64 %and24, %and27, !dbg !211
  %18 = load i64*, i64** %numbers.addr, align 8, !dbg !211
  %arrayidx29 = getelementptr inbounds i64, i64* %18, i64 2, !dbg !211
  %19 = load i64, i64* %arrayidx29, align 8, !dbg !211
  %shl30 = shl i64 %19, 0, !dbg !211
  %and31 = and i64 %shl30, 255, !dbg !211
  %or32 = or i64 %or28, %and31, !dbg !211
  store i64 %or32, i64* %dev, align 8, !dbg !213
  %20 = load i64, i64* %dev, align 8, !dbg !214
  %and33 = and i64 %20, 4293918720, !dbg !214
  %shr34 = lshr i64 %and33, 20, !dbg !214
  %conv35 = trunc i64 %shr34 to i32, !dbg !214
  %conv36 = sext i32 %conv35 to i64, !dbg !216
  %21 = load i64*, i64** %numbers.addr, align 8, !dbg !217
  %arrayidx37 = getelementptr inbounds i64, i64* %21, i64 0, !dbg !217
  %22 = load i64, i64* %arrayidx37, align 8, !dbg !217
  %cmp38 = icmp ne i64 %conv36, %22, !dbg !218
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !219

if.then40:                                        ; preds = %if.then21
  %23 = load i8**, i8*** %error.addr, align 8, !dbg !220
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %23, align 8, !dbg !221
  br label %if.end41, !dbg !222

if.end41:                                         ; preds = %if.then40, %if.then21
  %24 = load i64, i64* %dev, align 8, !dbg !223
  %and42 = and i64 %24, 1048320, !dbg !223
  %shr43 = lshr i64 %and42, 8, !dbg !223
  %conv44 = trunc i64 %shr43 to i32, !dbg !223
  %conv45 = sext i32 %conv44 to i64, !dbg !225
  %25 = load i64*, i64** %numbers.addr, align 8, !dbg !226
  %arrayidx46 = getelementptr inbounds i64, i64* %25, i64 1, !dbg !226
  %26 = load i64, i64* %arrayidx46, align 8, !dbg !226
  %cmp47 = icmp ne i64 %conv45, %26, !dbg !227
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !228

if.then49:                                        ; preds = %if.end41
  %27 = load i8**, i8*** %error.addr, align 8, !dbg !229
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.16, i32 0, i32 0), i8** %27, align 8, !dbg !230
  br label %if.end50, !dbg !231

if.end50:                                         ; preds = %if.then49, %if.end41
  %28 = load i64, i64* %dev, align 8, !dbg !232
  %and51 = and i64 %28, 255, !dbg !232
  %shr52 = lshr i64 %and51, 0, !dbg !232
  %conv53 = trunc i64 %shr52 to i32, !dbg !232
  %conv54 = sext i32 %conv53 to i64, !dbg !234
  %29 = load i64*, i64** %numbers.addr, align 8, !dbg !235
  %arrayidx55 = getelementptr inbounds i64, i64* %29, i64 2, !dbg !235
  %30 = load i64, i64* %arrayidx55, align 8, !dbg !235
  %cmp56 = icmp ne i64 %conv54, %30, !dbg !236
  br i1 %cmp56, label %if.then58, label %if.end59, !dbg !237

if.then58:                                        ; preds = %if.end50
  %31 = load i8**, i8*** %error.addr, align 8, !dbg !238
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.17, i32 0, i32 0), i8** %31, align 8, !dbg !239
  br label %if.end59, !dbg !240

if.end59:                                         ; preds = %if.then58, %if.end50
  br label %if.end61, !dbg !241

if.else60:                                        ; preds = %if.else
  %32 = load i8**, i8*** %error.addr, align 8, !dbg !242
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %32, align 8, !dbg !243
  br label %if.end61

if.end61:                                         ; preds = %if.else60, %if.end59
  br label %if.end62

if.end62:                                         ; preds = %if.end61, %if.end18
  %33 = load i64, i64* %dev, align 8, !dbg !244
  ret i64 %33, !dbg !245
}

; Function Attrs: nounwind uwtable
define internal i64 @pack_freebsd(i32 %n, i64* %numbers, i8** %error) #0 !dbg !29 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !246, metadata !61), !dbg !247
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !248, metadata !61), !dbg !249
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !250, metadata !61), !dbg !251
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !252, metadata !61), !dbg !253
  store i64 0, i64* %dev, align 8, !dbg !253
  %0 = load i32, i32* %n.addr, align 4, !dbg !254
  %cmp = icmp eq i32 %0, 2, !dbg !256
  br i1 %cmp, label %if.then, label %if.else, !dbg !257

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !258
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !258
  %2 = load i64, i64* %arrayidx, align 8, !dbg !258
  %shl = shl i64 %2, 8, !dbg !258
  %and = and i64 %shl, 65280, !dbg !258
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !258
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !258
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !258
  %shl2 = shl i64 %4, 0, !dbg !258
  %and3 = and i64 %shl2, 4294902015, !dbg !258
  %or = or i64 %and, %and3, !dbg !258
  store i64 %or, i64* %dev, align 8, !dbg !260
  %5 = load i64, i64* %dev, align 8, !dbg !261
  %and4 = and i64 %5, 65280, !dbg !261
  %shr = lshr i64 %and4, 8, !dbg !261
  %conv = trunc i64 %shr to i32, !dbg !261
  %conv5 = sext i32 %conv to i64, !dbg !263
  %6 = load i64*, i64** %numbers.addr, align 8, !dbg !264
  %arrayidx6 = getelementptr inbounds i64, i64* %6, i64 0, !dbg !264
  %7 = load i64, i64* %arrayidx6, align 8, !dbg !264
  %cmp7 = icmp ne i64 %conv5, %7, !dbg !265
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !266

if.then9:                                         ; preds = %if.then
  %8 = load i8**, i8*** %error.addr, align 8, !dbg !267
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %8, align 8, !dbg !268
  br label %if.end, !dbg !269

if.end:                                           ; preds = %if.then9, %if.then
  %9 = load i64, i64* %dev, align 8, !dbg !270
  %and10 = and i64 %9, 4294902015, !dbg !270
  %shr11 = lshr i64 %and10, 0, !dbg !270
  %conv12 = trunc i64 %shr11 to i32, !dbg !270
  %conv13 = sext i32 %conv12 to i64, !dbg !272
  %10 = load i64*, i64** %numbers.addr, align 8, !dbg !273
  %arrayidx14 = getelementptr inbounds i64, i64* %10, i64 1, !dbg !273
  %11 = load i64, i64* %arrayidx14, align 8, !dbg !273
  %cmp15 = icmp ne i64 %conv13, %11, !dbg !274
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !275

if.then17:                                        ; preds = %if.end
  %12 = load i8**, i8*** %error.addr, align 8, !dbg !276
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %12, align 8, !dbg !277
  br label %if.end18, !dbg !278

if.end18:                                         ; preds = %if.then17, %if.end
  br label %if.end19, !dbg !279

if.else:                                          ; preds = %entry
  %13 = load i8**, i8*** %error.addr, align 8, !dbg !280
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %13, align 8, !dbg !281
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.end18
  %14 = load i64, i64* %dev, align 8, !dbg !282
  ret i64 %14, !dbg !283
}

; Function Attrs: nounwind uwtable
define internal i64 @pack_8_24(i32 %n, i64* %numbers, i8** %error) #0 !dbg !30 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !284, metadata !61), !dbg !285
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !286, metadata !61), !dbg !287
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !288, metadata !61), !dbg !289
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !290, metadata !61), !dbg !291
  store i64 0, i64* %dev, align 8, !dbg !291
  %0 = load i32, i32* %n.addr, align 4, !dbg !292
  %cmp = icmp eq i32 %0, 2, !dbg !294
  br i1 %cmp, label %if.then, label %if.else, !dbg !295

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !296
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !296
  %2 = load i64, i64* %arrayidx, align 8, !dbg !296
  %shl = shl i64 %2, 24, !dbg !296
  %and = and i64 %shl, 4278190080, !dbg !296
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !296
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !296
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !296
  %shl2 = shl i64 %4, 0, !dbg !296
  %and3 = and i64 %shl2, 16777215, !dbg !296
  %or = or i64 %and, %and3, !dbg !296
  store i64 %or, i64* %dev, align 8, !dbg !298
  %5 = load i64, i64* %dev, align 8, !dbg !299
  %and4 = and i64 %5, 4278190080, !dbg !299
  %shr = lshr i64 %and4, 24, !dbg !299
  %conv = trunc i64 %shr to i32, !dbg !299
  %conv5 = sext i32 %conv to i64, !dbg !301
  %6 = load i64*, i64** %numbers.addr, align 8, !dbg !302
  %arrayidx6 = getelementptr inbounds i64, i64* %6, i64 0, !dbg !302
  %7 = load i64, i64* %arrayidx6, align 8, !dbg !302
  %cmp7 = icmp ne i64 %conv5, %7, !dbg !303
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !304

if.then9:                                         ; preds = %if.then
  %8 = load i8**, i8*** %error.addr, align 8, !dbg !305
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %8, align 8, !dbg !306
  br label %if.end, !dbg !307

if.end:                                           ; preds = %if.then9, %if.then
  %9 = load i64, i64* %dev, align 8, !dbg !308
  %and10 = and i64 %9, 16777215, !dbg !308
  %shr11 = lshr i64 %and10, 0, !dbg !308
  %conv12 = trunc i64 %shr11 to i32, !dbg !308
  %conv13 = sext i32 %conv12 to i64, !dbg !310
  %10 = load i64*, i64** %numbers.addr, align 8, !dbg !311
  %arrayidx14 = getelementptr inbounds i64, i64* %10, i64 1, !dbg !311
  %11 = load i64, i64* %arrayidx14, align 8, !dbg !311
  %cmp15 = icmp ne i64 %conv13, %11, !dbg !312
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !313

if.then17:                                        ; preds = %if.end
  %12 = load i8**, i8*** %error.addr, align 8, !dbg !314
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %12, align 8, !dbg !315
  br label %if.end18, !dbg !316

if.end18:                                         ; preds = %if.then17, %if.end
  br label %if.end19, !dbg !317

if.else:                                          ; preds = %entry
  %13 = load i8**, i8*** %error.addr, align 8, !dbg !318
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %13, align 8, !dbg !319
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.end18
  %14 = load i64, i64* %dev, align 8, !dbg !320
  ret i64 %14, !dbg !321
}

; Function Attrs: nounwind uwtable
define internal i64 @pack_netbsd(i32 %n, i64* %numbers, i8** %error) #0 !dbg !31 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !322, metadata !61), !dbg !323
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !324, metadata !61), !dbg !325
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !326, metadata !61), !dbg !327
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !328, metadata !61), !dbg !329
  store i64 0, i64* %dev, align 8, !dbg !329
  %0 = load i32, i32* %n.addr, align 4, !dbg !330
  %cmp = icmp eq i32 %0, 2, !dbg !332
  br i1 %cmp, label %if.then, label %if.else26, !dbg !333

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !334
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !334
  %2 = load i64, i64* %arrayidx, align 8, !dbg !334
  %shl = shl i64 %2, 8, !dbg !334
  %and = and i64 %shl, 1048320, !dbg !334
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !334
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !334
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !334
  %shl2 = shl i64 %4, 12, !dbg !334
  %and3 = and i64 %shl2, 4293918720, !dbg !334
  %or = or i64 %and, %and3, !dbg !334
  %5 = load i64*, i64** %numbers.addr, align 8, !dbg !334
  %arrayidx4 = getelementptr inbounds i64, i64* %5, i64 1, !dbg !334
  %6 = load i64, i64* %arrayidx4, align 8, !dbg !334
  %shl5 = shl i64 %6, 0, !dbg !334
  %and6 = and i64 %shl5, 255, !dbg !334
  %or7 = or i64 %or, %and6, !dbg !334
  store i64 %or7, i64* %dev, align 8, !dbg !336
  %7 = load i64, i64* %dev, align 8, !dbg !337
  %and8 = and i64 %7, 1048320, !dbg !337
  %shr = lshr i64 %and8, 8, !dbg !337
  %conv = trunc i64 %shr to i32, !dbg !337
  %conv9 = sext i32 %conv to i64, !dbg !339
  %8 = load i64*, i64** %numbers.addr, align 8, !dbg !340
  %arrayidx10 = getelementptr inbounds i64, i64* %8, i64 0, !dbg !340
  %9 = load i64, i64* %arrayidx10, align 8, !dbg !340
  %cmp11 = icmp ne i64 %conv9, %9, !dbg !341
  br i1 %cmp11, label %if.then13, label %if.else, !dbg !342

if.then13:                                        ; preds = %if.then
  %10 = load i8**, i8*** %error.addr, align 8, !dbg !343
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %10, align 8, !dbg !344
  br label %if.end25, !dbg !345

if.else:                                          ; preds = %if.then
  %11 = load i64, i64* %dev, align 8, !dbg !346
  %and14 = and i64 %11, 4293918720, !dbg !346
  %shr15 = lshr i64 %and14, 12, !dbg !346
  %12 = load i64, i64* %dev, align 8, !dbg !346
  %and16 = and i64 %12, 255, !dbg !346
  %shr17 = lshr i64 %and16, 0, !dbg !346
  %or18 = or i64 %shr15, %shr17, !dbg !346
  %conv19 = trunc i64 %or18 to i32, !dbg !346
  %conv20 = sext i32 %conv19 to i64, !dbg !348
  %13 = load i64*, i64** %numbers.addr, align 8, !dbg !349
  %arrayidx21 = getelementptr inbounds i64, i64* %13, i64 1, !dbg !349
  %14 = load i64, i64* %arrayidx21, align 8, !dbg !349
  %cmp22 = icmp ne i64 %conv20, %14, !dbg !350
  br i1 %cmp22, label %if.then24, label %if.end, !dbg !351

if.then24:                                        ; preds = %if.else
  %15 = load i8**, i8*** %error.addr, align 8, !dbg !352
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %15, align 8, !dbg !353
  br label %if.end, !dbg !354

if.end:                                           ; preds = %if.then24, %if.else
  br label %if.end25

if.end25:                                         ; preds = %if.end, %if.then13
  br label %if.end27, !dbg !355

if.else26:                                        ; preds = %entry
  %16 = load i8**, i8*** %error.addr, align 8, !dbg !356
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %16, align 8, !dbg !357
  br label %if.end27

if.end27:                                         ; preds = %if.else26, %if.end25
  %17 = load i64, i64* %dev, align 8, !dbg !358
  ret i64 %17, !dbg !359
}

; Function Attrs: nounwind uwtable
define internal i64 @pack_12_20(i32 %n, i64* %numbers, i8** %error) #0 !dbg !32 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !360, metadata !61), !dbg !361
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !362, metadata !61), !dbg !363
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !364, metadata !61), !dbg !365
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !366, metadata !61), !dbg !367
  store i64 0, i64* %dev, align 8, !dbg !367
  %0 = load i32, i32* %n.addr, align 4, !dbg !368
  %cmp = icmp eq i32 %0, 2, !dbg !370
  br i1 %cmp, label %if.then, label %if.else, !dbg !371

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !372
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !372
  %2 = load i64, i64* %arrayidx, align 8, !dbg !372
  %shl = shl i64 %2, 20, !dbg !372
  %and = and i64 %shl, 4293918720, !dbg !372
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !372
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !372
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !372
  %shl2 = shl i64 %4, 0, !dbg !372
  %and3 = and i64 %shl2, 1048575, !dbg !372
  %or = or i64 %and, %and3, !dbg !372
  store i64 %or, i64* %dev, align 8, !dbg !374
  %5 = load i64, i64* %dev, align 8, !dbg !375
  %and4 = and i64 %5, 4293918720, !dbg !375
  %shr = lshr i64 %and4, 20, !dbg !375
  %conv = trunc i64 %shr to i32, !dbg !375
  %conv5 = sext i32 %conv to i64, !dbg !377
  %6 = load i64*, i64** %numbers.addr, align 8, !dbg !378
  %arrayidx6 = getelementptr inbounds i64, i64* %6, i64 0, !dbg !378
  %7 = load i64, i64* %arrayidx6, align 8, !dbg !378
  %cmp7 = icmp ne i64 %conv5, %7, !dbg !379
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !380

if.then9:                                         ; preds = %if.then
  %8 = load i8**, i8*** %error.addr, align 8, !dbg !381
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %8, align 8, !dbg !382
  br label %if.end, !dbg !383

if.end:                                           ; preds = %if.then9, %if.then
  %9 = load i64, i64* %dev, align 8, !dbg !384
  %and10 = and i64 %9, 1048575, !dbg !384
  %shr11 = lshr i64 %and10, 0, !dbg !384
  %conv12 = trunc i64 %shr11 to i32, !dbg !384
  %conv13 = sext i32 %conv12 to i64, !dbg !386
  %10 = load i64*, i64** %numbers.addr, align 8, !dbg !387
  %arrayidx14 = getelementptr inbounds i64, i64* %10, i64 1, !dbg !387
  %11 = load i64, i64* %arrayidx14, align 8, !dbg !387
  %cmp15 = icmp ne i64 %conv13, %11, !dbg !388
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !389

if.then17:                                        ; preds = %if.end
  %12 = load i8**, i8*** %error.addr, align 8, !dbg !390
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %12, align 8, !dbg !391
  br label %if.end18, !dbg !392

if.end18:                                         ; preds = %if.then17, %if.end
  br label %if.end19, !dbg !393

if.else:                                          ; preds = %entry
  %13 = load i8**, i8*** %error.addr, align 8, !dbg !394
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %13, align 8, !dbg !395
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.end18
  %14 = load i64, i64* %dev, align 8, !dbg !396
  ret i64 %14, !dbg !397
}

; Function Attrs: nounwind uwtable
define internal i64 @pack_14_18(i32 %n, i64* %numbers, i8** %error) #0 !dbg !33 {
entry:
  %n.addr = alloca i32, align 4
  %numbers.addr = alloca i64*, align 8
  %error.addr = alloca i8**, align 8
  %dev = alloca i64, align 8
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !398, metadata !61), !dbg !399
  store i64* %numbers, i64** %numbers.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %numbers.addr, metadata !400, metadata !61), !dbg !401
  store i8** %error, i8*** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %error.addr, metadata !402, metadata !61), !dbg !403
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !404, metadata !61), !dbg !405
  store i64 0, i64* %dev, align 8, !dbg !405
  %0 = load i32, i32* %n.addr, align 4, !dbg !406
  %cmp = icmp eq i32 %0, 2, !dbg !408
  br i1 %cmp, label %if.then, label %if.else, !dbg !409

if.then:                                          ; preds = %entry
  %1 = load i64*, i64** %numbers.addr, align 8, !dbg !410
  %arrayidx = getelementptr inbounds i64, i64* %1, i64 0, !dbg !410
  %2 = load i64, i64* %arrayidx, align 8, !dbg !410
  %shl = shl i64 %2, 18, !dbg !410
  %and = and i64 %shl, 4294705152, !dbg !410
  %3 = load i64*, i64** %numbers.addr, align 8, !dbg !410
  %arrayidx1 = getelementptr inbounds i64, i64* %3, i64 1, !dbg !410
  %4 = load i64, i64* %arrayidx1, align 8, !dbg !410
  %shl2 = shl i64 %4, 0, !dbg !410
  %and3 = and i64 %shl2, 262143, !dbg !410
  %or = or i64 %and, %and3, !dbg !410
  store i64 %or, i64* %dev, align 8, !dbg !412
  %5 = load i64, i64* %dev, align 8, !dbg !413
  %and4 = and i64 %5, 4294705152, !dbg !413
  %shr = lshr i64 %and4, 18, !dbg !413
  %conv = trunc i64 %shr to i32, !dbg !413
  %conv5 = sext i32 %conv to i64, !dbg !415
  %6 = load i64*, i64** %numbers.addr, align 8, !dbg !416
  %arrayidx6 = getelementptr inbounds i64, i64* %6, i64 0, !dbg !416
  %7 = load i64, i64* %arrayidx6, align 8, !dbg !416
  %cmp7 = icmp ne i64 %conv5, %7, !dbg !417
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !418

if.then9:                                         ; preds = %if.then
  %8 = load i8**, i8*** %error.addr, align 8, !dbg !419
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMajorError, i32 0, i32 0), i8** %8, align 8, !dbg !420
  br label %if.end, !dbg !421

if.end:                                           ; preds = %if.then9, %if.then
  %9 = load i64, i64* %dev, align 8, !dbg !422
  %and10 = and i64 %9, 262143, !dbg !422
  %shr11 = lshr i64 %and10, 0, !dbg !422
  %conv12 = trunc i64 %shr11 to i32, !dbg !422
  %conv13 = sext i32 %conv12 to i64, !dbg !424
  %10 = load i64*, i64** %numbers.addr, align 8, !dbg !425
  %arrayidx14 = getelementptr inbounds i64, i64* %10, i64 1, !dbg !425
  %11 = load i64, i64* %arrayidx14, align 8, !dbg !425
  %cmp15 = icmp ne i64 %conv13, %11, !dbg !426
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !427

if.then17:                                        ; preds = %if.end
  %12 = load i8**, i8*** %error.addr, align 8, !dbg !428
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @iMinorError, i32 0, i32 0), i8** %12, align 8, !dbg !429
  br label %if.end18, !dbg !430

if.end18:                                         ; preds = %if.then17, %if.end
  br label %if.end19, !dbg !431

if.else:                                          ; preds = %entry
  %13 = load i8**, i8*** %error.addr, align 8, !dbg !432
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @tooManyFields, i32 0, i32 0), i8** %13, align 8, !dbg !433
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.end18
  %14 = load i64, i64* %dev, align 8, !dbg !434
  ret i64 %14, !dbg !435
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!57, !58}
!llvm.ident = !{!59}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !12, globals: !39)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_pack_dev.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !9}
!4 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!5 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !6, line: 60, baseType: !7)
!6 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !8, line: 124, baseType: !4)
!8 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "int32_t", file: !10, line: 38, baseType: !11)
!10 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!12 = !{!13, !21, !27, !28, !29, !30, !31, !32, !33, !34}
!13 = distinct !DISubprogram(name: "pack_native", scope: !1, file: !1, line: 106, type: !14, isLocal: false, isDefinition: true, scopeLine: 107, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!14 = !DISubroutineType(types: !15)
!15 = !{!5, !11, !16, !17}
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!20 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!21 = distinct !DISubprogram(name: "pack_find", scope: !1, file: !1, line: 319, type: !22, isLocal: false, isDefinition: true, scopeLine: 320, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!22 = !DISubroutineType(types: !23)
!23 = !{!24, !18}
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "pack_t", file: !26, line: 37, baseType: !14)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_pack_dev.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!27 = distinct !DISubprogram(name: "pack_8_8", scope: !1, file: !1, line: 167, type: !14, isLocal: true, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!28 = distinct !DISubprogram(name: "pack_bsdos", scope: !1, file: !1, line: 257, type: !14, isLocal: true, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!29 = distinct !DISubprogram(name: "pack_freebsd", scope: !1, file: !1, line: 145, type: !14, isLocal: true, isDefinition: true, scopeLine: 146, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!30 = distinct !DISubprogram(name: "pack_8_24", scope: !1, file: !1, line: 233, type: !14, isLocal: true, isDefinition: true, scopeLine: 234, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = distinct !DISubprogram(name: "pack_netbsd", scope: !1, file: !1, line: 123, type: !14, isLocal: true, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = distinct !DISubprogram(name: "pack_12_20", scope: !1, file: !1, line: 189, type: !14, isLocal: true, isDefinition: true, scopeLine: 190, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!33 = distinct !DISubprogram(name: "pack_14_18", scope: !1, file: !1, line: 211, type: !14, isLocal: true, isDefinition: true, scopeLine: 212, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!34 = distinct !DISubprogram(name: "compare_format", scope: !1, file: !1, line: 306, type: !35, isLocal: true, isDefinition: true, scopeLine: 307, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!35 = !DISubroutineType(types: !36)
!36 = !{!11, !37, !37}
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!39 = !{!40, !44, !45, !49}
!40 = !DIGlobalVariable(name: "iMajorError", scope: !0, file: !1, line: 75, type: !41, isLocal: true, isDefinition: true, variable: [21 x i8]* @iMajorError)
!41 = !DICompositeType(tag: DW_TAG_array_type, baseType: !19, size: 168, align: 8, elements: !42)
!42 = !{!43}
!43 = !DISubrange(count: 21)
!44 = !DIGlobalVariable(name: "iMinorError", scope: !0, file: !1, line: 76, type: !41, isLocal: true, isDefinition: true, variable: [21 x i8]* @iMinorError)
!45 = !DIGlobalVariable(name: "tooManyFields", scope: !0, file: !1, line: 77, type: !46, isLocal: true, isDefinition: true, variable: [27 x i8]* @tooManyFields)
!46 = !DICompositeType(tag: DW_TAG_array_type, baseType: !19, size: 216, align: 8, elements: !47)
!47 = !{!48}
!48 = !DISubrange(count: 27)
!49 = !DIGlobalVariable(name: "formats", scope: !0, file: !1, line: 286, type: !50, isLocal: true, isDefinition: true, variable: [16 x %struct.format]* @formats)
!50 = !DICompositeType(tag: DW_TAG_array_type, baseType: !51, size: 2048, align: 64, elements: !55)
!51 = !DICompositeType(tag: DW_TAG_structure_type, name: "format", file: !1, line: 283, size: 128, align: 64, elements: !52)
!52 = !{!53, !54}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !51, file: !1, line: 284, baseType: !18, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "pack", scope: !51, file: !1, line: 285, baseType: !24, size: 64, align: 64, offset: 64)
!55 = !{!56}
!56 = !DISubrange(count: 16)
!57 = !{i32 2, !"Dwarf Version", i32 4}
!58 = !{i32 2, !"Debug Info Version", i32 3}
!59 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!60 = !DILocalVariable(name: "n", arg: 1, scope: !13, file: !1, line: 106, type: !11)
!61 = !DIExpression()
!62 = !DILocation(line: 106, column: 17, scope: !13)
!63 = !DILocalVariable(name: "numbers", arg: 2, scope: !13, file: !1, line: 106, type: !16)
!64 = !DILocation(line: 106, column: 34, scope: !13)
!65 = !DILocalVariable(name: "error", arg: 3, scope: !13, file: !1, line: 106, type: !17)
!66 = !DILocation(line: 106, column: 58, scope: !13)
!67 = !DILocalVariable(name: "dev", scope: !13, file: !1, line: 108, type: !5)
!68 = !DILocation(line: 108, column: 8, scope: !13)
!69 = !DILocation(line: 110, column: 6, scope: !70)
!70 = distinct !DILexicalBlock(scope: !13, file: !1, line: 110, column: 6)
!71 = !DILocation(line: 110, column: 8, scope: !70)
!72 = !DILocation(line: 110, column: 6, scope: !13)
!73 = !DILocation(line: 111, column: 9, scope: !74)
!74 = distinct !DILexicalBlock(scope: !70, file: !1, line: 110, column: 14)
!75 = !DILocation(line: 111, column: 7, scope: !74)
!76 = !DILocation(line: 112, column: 22, scope: !77)
!77 = distinct !DILexicalBlock(scope: !74, file: !1, line: 112, column: 7)
!78 = !DILocation(line: 112, column: 7, scope: !77)
!79 = !DILocation(line: 112, column: 36, scope: !77)
!80 = !DILocation(line: 112, column: 33, scope: !77)
!81 = !DILocation(line: 112, column: 7, scope: !74)
!82 = !DILocation(line: 113, column: 5, scope: !77)
!83 = !DILocation(line: 113, column: 11, scope: !77)
!84 = !DILocation(line: 113, column: 4, scope: !77)
!85 = !DILocation(line: 114, column: 27, scope: !86)
!86 = distinct !DILexicalBlock(scope: !77, file: !1, line: 114, column: 12)
!87 = !DILocation(line: 114, column: 12, scope: !86)
!88 = !DILocation(line: 114, column: 41, scope: !86)
!89 = !DILocation(line: 114, column: 38, scope: !86)
!90 = !DILocation(line: 114, column: 12, scope: !77)
!91 = !DILocation(line: 115, column: 5, scope: !86)
!92 = !DILocation(line: 115, column: 11, scope: !86)
!93 = !DILocation(line: 115, column: 4, scope: !86)
!94 = !DILocation(line: 116, column: 2, scope: !74)
!95 = !DILocation(line: 117, column: 4, scope: !70)
!96 = !DILocation(line: 117, column: 10, scope: !70)
!97 = !DILocation(line: 118, column: 10, scope: !13)
!98 = !DILocation(line: 118, column: 2, scope: !13)
!99 = !DILocalVariable(name: "name", arg: 1, scope: !21, file: !1, line: 319, type: !18)
!100 = !DILocation(line: 319, column: 23, scope: !21)
!101 = !DILocalVariable(name: "format", scope: !21, file: !1, line: 321, type: !102)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!103 = !DILocation(line: 321, column: 17, scope: !21)
!104 = !DILocation(line: 323, column: 19, scope: !21)
!105 = !DILocation(line: 323, column: 11, scope: !21)
!106 = !DILocation(line: 323, column: 9, scope: !21)
!107 = !DILocation(line: 326, column: 6, scope: !108)
!108 = distinct !DILexicalBlock(scope: !21, file: !1, line: 326, column: 6)
!109 = !DILocation(line: 326, column: 13, scope: !108)
!110 = !DILocation(line: 326, column: 6, scope: !21)
!111 = !DILocation(line: 327, column: 3, scope: !108)
!112 = !DILocation(line: 328, column: 10, scope: !21)
!113 = !DILocation(line: 328, column: 18, scope: !21)
!114 = !DILocation(line: 328, column: 2, scope: !21)
!115 = !DILocation(line: 329, column: 1, scope: !21)
!116 = !DILocalVariable(name: "key", arg: 1, scope: !34, file: !1, line: 306, type: !37)
!117 = !DILocation(line: 306, column: 28, scope: !34)
!118 = !DILocalVariable(name: "element", arg: 2, scope: !34, file: !1, line: 306, type: !37)
!119 = !DILocation(line: 306, column: 45, scope: !34)
!120 = !DILocalVariable(name: "name", scope: !34, file: !1, line: 308, type: !18)
!121 = !DILocation(line: 308, column: 15, scope: !34)
!122 = !DILocalVariable(name: "format", scope: !34, file: !1, line: 309, type: !123)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !51)
!125 = !DILocation(line: 309, column: 23, scope: !34)
!126 = !DILocation(line: 311, column: 9, scope: !34)
!127 = !DILocation(line: 311, column: 7, scope: !34)
!128 = !DILocation(line: 312, column: 11, scope: !34)
!129 = !DILocation(line: 312, column: 9, scope: !34)
!130 = !DILocation(line: 314, column: 17, scope: !34)
!131 = !DILocation(line: 314, column: 23, scope: !34)
!132 = !DILocation(line: 314, column: 31, scope: !34)
!133 = !DILocation(line: 314, column: 10, scope: !34)
!134 = !DILocation(line: 314, column: 2, scope: !34)
!135 = !DILocalVariable(name: "n", arg: 1, scope: !27, file: !1, line: 167, type: !11)
!136 = !DILocation(line: 167, column: 14, scope: !27)
!137 = !DILocalVariable(name: "numbers", arg: 2, scope: !27, file: !1, line: 167, type: !16)
!138 = !DILocation(line: 167, column: 31, scope: !27)
!139 = !DILocalVariable(name: "error", arg: 3, scope: !27, file: !1, line: 167, type: !17)
!140 = !DILocation(line: 167, column: 55, scope: !27)
!141 = !DILocalVariable(name: "dev", scope: !27, file: !1, line: 169, type: !5)
!142 = !DILocation(line: 169, column: 8, scope: !27)
!143 = !DILocation(line: 171, column: 6, scope: !144)
!144 = distinct !DILexicalBlock(scope: !27, file: !1, line: 171, column: 6)
!145 = !DILocation(line: 171, column: 8, scope: !144)
!146 = !DILocation(line: 171, column: 6, scope: !27)
!147 = !DILocation(line: 172, column: 9, scope: !148)
!148 = distinct !DILexicalBlock(scope: !144, file: !1, line: 171, column: 14)
!149 = !DILocation(line: 172, column: 7, scope: !148)
!150 = !DILocation(line: 173, column: 22, scope: !151)
!151 = distinct !DILexicalBlock(scope: !148, file: !1, line: 173, column: 7)
!152 = !DILocation(line: 173, column: 7, scope: !151)
!153 = !DILocation(line: 173, column: 40, scope: !151)
!154 = !DILocation(line: 173, column: 37, scope: !151)
!155 = !DILocation(line: 173, column: 7, scope: !148)
!156 = !DILocation(line: 174, column: 5, scope: !151)
!157 = !DILocation(line: 174, column: 11, scope: !151)
!158 = !DILocation(line: 174, column: 4, scope: !151)
!159 = !DILocation(line: 175, column: 22, scope: !160)
!160 = distinct !DILexicalBlock(scope: !148, file: !1, line: 175, column: 7)
!161 = !DILocation(line: 175, column: 7, scope: !160)
!162 = !DILocation(line: 175, column: 40, scope: !160)
!163 = !DILocation(line: 175, column: 37, scope: !160)
!164 = !DILocation(line: 175, column: 7, scope: !148)
!165 = !DILocation(line: 176, column: 5, scope: !160)
!166 = !DILocation(line: 176, column: 11, scope: !160)
!167 = !DILocation(line: 176, column: 4, scope: !160)
!168 = !DILocation(line: 177, column: 2, scope: !148)
!169 = !DILocation(line: 178, column: 4, scope: !144)
!170 = !DILocation(line: 178, column: 10, scope: !144)
!171 = !DILocation(line: 179, column: 10, scope: !27)
!172 = !DILocation(line: 179, column: 2, scope: !27)
!173 = !DILocalVariable(name: "n", arg: 1, scope: !28, file: !1, line: 257, type: !11)
!174 = !DILocation(line: 257, column: 16, scope: !28)
!175 = !DILocalVariable(name: "numbers", arg: 2, scope: !28, file: !1, line: 257, type: !16)
!176 = !DILocation(line: 257, column: 33, scope: !28)
!177 = !DILocalVariable(name: "error", arg: 3, scope: !28, file: !1, line: 257, type: !17)
!178 = !DILocation(line: 257, column: 57, scope: !28)
!179 = !DILocalVariable(name: "dev", scope: !28, file: !1, line: 259, type: !5)
!180 = !DILocation(line: 259, column: 8, scope: !28)
!181 = !DILocation(line: 261, column: 6, scope: !182)
!182 = distinct !DILexicalBlock(scope: !28, file: !1, line: 261, column: 6)
!183 = !DILocation(line: 261, column: 8, scope: !182)
!184 = !DILocation(line: 261, column: 6, scope: !28)
!185 = !DILocation(line: 262, column: 9, scope: !186)
!186 = distinct !DILexicalBlock(scope: !182, file: !1, line: 261, column: 14)
!187 = !DILocation(line: 262, column: 7, scope: !186)
!188 = !DILocation(line: 263, column: 22, scope: !189)
!189 = distinct !DILexicalBlock(scope: !186, file: !1, line: 263, column: 7)
!190 = !DILocation(line: 263, column: 7, scope: !189)
!191 = !DILocation(line: 263, column: 42, scope: !189)
!192 = !DILocation(line: 263, column: 39, scope: !189)
!193 = !DILocation(line: 263, column: 7, scope: !186)
!194 = !DILocation(line: 264, column: 5, scope: !189)
!195 = !DILocation(line: 264, column: 11, scope: !189)
!196 = !DILocation(line: 264, column: 4, scope: !189)
!197 = !DILocation(line: 265, column: 22, scope: !198)
!198 = distinct !DILexicalBlock(scope: !186, file: !1, line: 265, column: 7)
!199 = !DILocation(line: 265, column: 7, scope: !198)
!200 = !DILocation(line: 265, column: 42, scope: !198)
!201 = !DILocation(line: 265, column: 39, scope: !198)
!202 = !DILocation(line: 265, column: 7, scope: !186)
!203 = !DILocation(line: 266, column: 5, scope: !198)
!204 = !DILocation(line: 266, column: 11, scope: !198)
!205 = !DILocation(line: 266, column: 4, scope: !198)
!206 = !DILocation(line: 267, column: 2, scope: !186)
!207 = !DILocation(line: 267, column: 13, scope: !208)
!208 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 1)
!209 = distinct !DILexicalBlock(scope: !182, file: !1, line: 267, column: 13)
!210 = !DILocation(line: 267, column: 15, scope: !208)
!211 = !DILocation(line: 268, column: 9, scope: !212)
!212 = distinct !DILexicalBlock(scope: !209, file: !1, line: 267, column: 21)
!213 = !DILocation(line: 268, column: 7, scope: !212)
!214 = !DILocation(line: 269, column: 22, scope: !215)
!215 = distinct !DILexicalBlock(scope: !212, file: !1, line: 269, column: 7)
!216 = !DILocation(line: 269, column: 7, scope: !215)
!217 = !DILocation(line: 269, column: 44, scope: !215)
!218 = !DILocation(line: 269, column: 41, scope: !215)
!219 = !DILocation(line: 269, column: 7, scope: !212)
!220 = !DILocation(line: 270, column: 5, scope: !215)
!221 = !DILocation(line: 270, column: 11, scope: !215)
!222 = !DILocation(line: 270, column: 4, scope: !215)
!223 = !DILocation(line: 271, column: 22, scope: !224)
!224 = distinct !DILexicalBlock(scope: !212, file: !1, line: 271, column: 7)
!225 = !DILocation(line: 271, column: 7, scope: !224)
!226 = !DILocation(line: 271, column: 43, scope: !224)
!227 = !DILocation(line: 271, column: 40, scope: !224)
!228 = !DILocation(line: 271, column: 7, scope: !212)
!229 = !DILocation(line: 272, column: 5, scope: !224)
!230 = !DILocation(line: 272, column: 11, scope: !224)
!231 = !DILocation(line: 272, column: 4, scope: !224)
!232 = !DILocation(line: 273, column: 22, scope: !233)
!233 = distinct !DILexicalBlock(scope: !212, file: !1, line: 273, column: 7)
!234 = !DILocation(line: 273, column: 7, scope: !233)
!235 = !DILocation(line: 273, column: 46, scope: !233)
!236 = !DILocation(line: 273, column: 43, scope: !233)
!237 = !DILocation(line: 273, column: 7, scope: !212)
!238 = !DILocation(line: 274, column: 5, scope: !233)
!239 = !DILocation(line: 274, column: 11, scope: !233)
!240 = !DILocation(line: 274, column: 4, scope: !233)
!241 = !DILocation(line: 275, column: 2, scope: !212)
!242 = !DILocation(line: 276, column: 4, scope: !209)
!243 = !DILocation(line: 276, column: 10, scope: !209)
!244 = !DILocation(line: 277, column: 10, scope: !28)
!245 = !DILocation(line: 277, column: 2, scope: !28)
!246 = !DILocalVariable(name: "n", arg: 1, scope: !29, file: !1, line: 145, type: !11)
!247 = !DILocation(line: 145, column: 18, scope: !29)
!248 = !DILocalVariable(name: "numbers", arg: 2, scope: !29, file: !1, line: 145, type: !16)
!249 = !DILocation(line: 145, column: 35, scope: !29)
!250 = !DILocalVariable(name: "error", arg: 3, scope: !29, file: !1, line: 145, type: !17)
!251 = !DILocation(line: 145, column: 59, scope: !29)
!252 = !DILocalVariable(name: "dev", scope: !29, file: !1, line: 147, type: !5)
!253 = !DILocation(line: 147, column: 8, scope: !29)
!254 = !DILocation(line: 149, column: 6, scope: !255)
!255 = distinct !DILexicalBlock(scope: !29, file: !1, line: 149, column: 6)
!256 = !DILocation(line: 149, column: 8, scope: !255)
!257 = !DILocation(line: 149, column: 6, scope: !29)
!258 = !DILocation(line: 150, column: 9, scope: !259)
!259 = distinct !DILexicalBlock(scope: !255, file: !1, line: 149, column: 14)
!260 = !DILocation(line: 150, column: 7, scope: !259)
!261 = !DILocation(line: 151, column: 22, scope: !262)
!262 = distinct !DILexicalBlock(scope: !259, file: !1, line: 151, column: 7)
!263 = !DILocation(line: 151, column: 7, scope: !262)
!264 = !DILocation(line: 151, column: 44, scope: !262)
!265 = !DILocation(line: 151, column: 41, scope: !262)
!266 = !DILocation(line: 151, column: 7, scope: !259)
!267 = !DILocation(line: 152, column: 5, scope: !262)
!268 = !DILocation(line: 152, column: 11, scope: !262)
!269 = !DILocation(line: 152, column: 4, scope: !262)
!270 = !DILocation(line: 153, column: 22, scope: !271)
!271 = distinct !DILexicalBlock(scope: !259, file: !1, line: 153, column: 7)
!272 = !DILocation(line: 153, column: 7, scope: !271)
!273 = !DILocation(line: 153, column: 44, scope: !271)
!274 = !DILocation(line: 153, column: 41, scope: !271)
!275 = !DILocation(line: 153, column: 7, scope: !259)
!276 = !DILocation(line: 154, column: 5, scope: !271)
!277 = !DILocation(line: 154, column: 11, scope: !271)
!278 = !DILocation(line: 154, column: 4, scope: !271)
!279 = !DILocation(line: 155, column: 2, scope: !259)
!280 = !DILocation(line: 156, column: 4, scope: !255)
!281 = !DILocation(line: 156, column: 10, scope: !255)
!282 = !DILocation(line: 157, column: 10, scope: !29)
!283 = !DILocation(line: 157, column: 2, scope: !29)
!284 = !DILocalVariable(name: "n", arg: 1, scope: !30, file: !1, line: 233, type: !11)
!285 = !DILocation(line: 233, column: 15, scope: !30)
!286 = !DILocalVariable(name: "numbers", arg: 2, scope: !30, file: !1, line: 233, type: !16)
!287 = !DILocation(line: 233, column: 32, scope: !30)
!288 = !DILocalVariable(name: "error", arg: 3, scope: !30, file: !1, line: 233, type: !17)
!289 = !DILocation(line: 233, column: 56, scope: !30)
!290 = !DILocalVariable(name: "dev", scope: !30, file: !1, line: 235, type: !5)
!291 = !DILocation(line: 235, column: 8, scope: !30)
!292 = !DILocation(line: 237, column: 6, scope: !293)
!293 = distinct !DILexicalBlock(scope: !30, file: !1, line: 237, column: 6)
!294 = !DILocation(line: 237, column: 8, scope: !293)
!295 = !DILocation(line: 237, column: 6, scope: !30)
!296 = !DILocation(line: 238, column: 9, scope: !297)
!297 = distinct !DILexicalBlock(scope: !293, file: !1, line: 237, column: 14)
!298 = !DILocation(line: 238, column: 7, scope: !297)
!299 = !DILocation(line: 239, column: 22, scope: !300)
!300 = distinct !DILexicalBlock(scope: !297, file: !1, line: 239, column: 7)
!301 = !DILocation(line: 239, column: 7, scope: !300)
!302 = !DILocation(line: 239, column: 41, scope: !300)
!303 = !DILocation(line: 239, column: 38, scope: !300)
!304 = !DILocation(line: 239, column: 7, scope: !297)
!305 = !DILocation(line: 240, column: 5, scope: !300)
!306 = !DILocation(line: 240, column: 11, scope: !300)
!307 = !DILocation(line: 240, column: 4, scope: !300)
!308 = !DILocation(line: 241, column: 22, scope: !309)
!309 = distinct !DILexicalBlock(scope: !297, file: !1, line: 241, column: 7)
!310 = !DILocation(line: 241, column: 7, scope: !309)
!311 = !DILocation(line: 241, column: 41, scope: !309)
!312 = !DILocation(line: 241, column: 38, scope: !309)
!313 = !DILocation(line: 241, column: 7, scope: !297)
!314 = !DILocation(line: 242, column: 5, scope: !309)
!315 = !DILocation(line: 242, column: 11, scope: !309)
!316 = !DILocation(line: 242, column: 4, scope: !309)
!317 = !DILocation(line: 243, column: 2, scope: !297)
!318 = !DILocation(line: 244, column: 4, scope: !293)
!319 = !DILocation(line: 244, column: 10, scope: !293)
!320 = !DILocation(line: 245, column: 10, scope: !30)
!321 = !DILocation(line: 245, column: 2, scope: !30)
!322 = !DILocalVariable(name: "n", arg: 1, scope: !31, file: !1, line: 123, type: !11)
!323 = !DILocation(line: 123, column: 17, scope: !31)
!324 = !DILocalVariable(name: "numbers", arg: 2, scope: !31, file: !1, line: 123, type: !16)
!325 = !DILocation(line: 123, column: 34, scope: !31)
!326 = !DILocalVariable(name: "error", arg: 3, scope: !31, file: !1, line: 123, type: !17)
!327 = !DILocation(line: 123, column: 58, scope: !31)
!328 = !DILocalVariable(name: "dev", scope: !31, file: !1, line: 125, type: !5)
!329 = !DILocation(line: 125, column: 8, scope: !31)
!330 = !DILocation(line: 127, column: 6, scope: !331)
!331 = distinct !DILexicalBlock(scope: !31, file: !1, line: 127, column: 6)
!332 = !DILocation(line: 127, column: 8, scope: !331)
!333 = !DILocation(line: 127, column: 6, scope: !31)
!334 = !DILocation(line: 128, column: 9, scope: !335)
!335 = distinct !DILexicalBlock(scope: !331, file: !1, line: 127, column: 14)
!336 = !DILocation(line: 128, column: 7, scope: !335)
!337 = !DILocation(line: 129, column: 22, scope: !338)
!338 = distinct !DILexicalBlock(scope: !335, file: !1, line: 129, column: 7)
!339 = !DILocation(line: 129, column: 7, scope: !338)
!340 = !DILocation(line: 129, column: 43, scope: !338)
!341 = !DILocation(line: 129, column: 40, scope: !338)
!342 = !DILocation(line: 129, column: 7, scope: !335)
!343 = !DILocation(line: 130, column: 5, scope: !338)
!344 = !DILocation(line: 130, column: 11, scope: !338)
!345 = !DILocation(line: 130, column: 4, scope: !338)
!346 = !DILocation(line: 131, column: 27, scope: !347)
!347 = distinct !DILexicalBlock(scope: !338, file: !1, line: 131, column: 12)
!348 = !DILocation(line: 131, column: 12, scope: !347)
!349 = !DILocation(line: 131, column: 48, scope: !347)
!350 = !DILocation(line: 131, column: 45, scope: !347)
!351 = !DILocation(line: 131, column: 12, scope: !338)
!352 = !DILocation(line: 132, column: 5, scope: !347)
!353 = !DILocation(line: 132, column: 11, scope: !347)
!354 = !DILocation(line: 132, column: 4, scope: !347)
!355 = !DILocation(line: 133, column: 2, scope: !335)
!356 = !DILocation(line: 134, column: 4, scope: !331)
!357 = !DILocation(line: 134, column: 10, scope: !331)
!358 = !DILocation(line: 135, column: 10, scope: !31)
!359 = !DILocation(line: 135, column: 2, scope: !31)
!360 = !DILocalVariable(name: "n", arg: 1, scope: !32, file: !1, line: 189, type: !11)
!361 = !DILocation(line: 189, column: 16, scope: !32)
!362 = !DILocalVariable(name: "numbers", arg: 2, scope: !32, file: !1, line: 189, type: !16)
!363 = !DILocation(line: 189, column: 33, scope: !32)
!364 = !DILocalVariable(name: "error", arg: 3, scope: !32, file: !1, line: 189, type: !17)
!365 = !DILocation(line: 189, column: 57, scope: !32)
!366 = !DILocalVariable(name: "dev", scope: !32, file: !1, line: 191, type: !5)
!367 = !DILocation(line: 191, column: 8, scope: !32)
!368 = !DILocation(line: 193, column: 6, scope: !369)
!369 = distinct !DILexicalBlock(scope: !32, file: !1, line: 193, column: 6)
!370 = !DILocation(line: 193, column: 8, scope: !369)
!371 = !DILocation(line: 193, column: 6, scope: !32)
!372 = !DILocation(line: 194, column: 9, scope: !373)
!373 = distinct !DILexicalBlock(scope: !369, file: !1, line: 193, column: 14)
!374 = !DILocation(line: 194, column: 7, scope: !373)
!375 = !DILocation(line: 195, column: 22, scope: !376)
!376 = distinct !DILexicalBlock(scope: !373, file: !1, line: 195, column: 7)
!377 = !DILocation(line: 195, column: 7, scope: !376)
!378 = !DILocation(line: 195, column: 42, scope: !376)
!379 = !DILocation(line: 195, column: 39, scope: !376)
!380 = !DILocation(line: 195, column: 7, scope: !373)
!381 = !DILocation(line: 196, column: 5, scope: !376)
!382 = !DILocation(line: 196, column: 11, scope: !376)
!383 = !DILocation(line: 196, column: 4, scope: !376)
!384 = !DILocation(line: 197, column: 22, scope: !385)
!385 = distinct !DILexicalBlock(scope: !373, file: !1, line: 197, column: 7)
!386 = !DILocation(line: 197, column: 7, scope: !385)
!387 = !DILocation(line: 197, column: 42, scope: !385)
!388 = !DILocation(line: 197, column: 39, scope: !385)
!389 = !DILocation(line: 197, column: 7, scope: !373)
!390 = !DILocation(line: 198, column: 5, scope: !385)
!391 = !DILocation(line: 198, column: 11, scope: !385)
!392 = !DILocation(line: 198, column: 4, scope: !385)
!393 = !DILocation(line: 199, column: 2, scope: !373)
!394 = !DILocation(line: 200, column: 4, scope: !369)
!395 = !DILocation(line: 200, column: 10, scope: !369)
!396 = !DILocation(line: 201, column: 10, scope: !32)
!397 = !DILocation(line: 201, column: 2, scope: !32)
!398 = !DILocalVariable(name: "n", arg: 1, scope: !33, file: !1, line: 211, type: !11)
!399 = !DILocation(line: 211, column: 16, scope: !33)
!400 = !DILocalVariable(name: "numbers", arg: 2, scope: !33, file: !1, line: 211, type: !16)
!401 = !DILocation(line: 211, column: 33, scope: !33)
!402 = !DILocalVariable(name: "error", arg: 3, scope: !33, file: !1, line: 211, type: !17)
!403 = !DILocation(line: 211, column: 57, scope: !33)
!404 = !DILocalVariable(name: "dev", scope: !33, file: !1, line: 213, type: !5)
!405 = !DILocation(line: 213, column: 8, scope: !33)
!406 = !DILocation(line: 215, column: 6, scope: !407)
!407 = distinct !DILexicalBlock(scope: !33, file: !1, line: 215, column: 6)
!408 = !DILocation(line: 215, column: 8, scope: !407)
!409 = !DILocation(line: 215, column: 6, scope: !33)
!410 = !DILocation(line: 216, column: 9, scope: !411)
!411 = distinct !DILexicalBlock(scope: !407, file: !1, line: 215, column: 14)
!412 = !DILocation(line: 216, column: 7, scope: !411)
!413 = !DILocation(line: 217, column: 22, scope: !414)
!414 = distinct !DILexicalBlock(scope: !411, file: !1, line: 217, column: 7)
!415 = !DILocation(line: 217, column: 7, scope: !414)
!416 = !DILocation(line: 217, column: 42, scope: !414)
!417 = !DILocation(line: 217, column: 39, scope: !414)
!418 = !DILocation(line: 217, column: 7, scope: !411)
!419 = !DILocation(line: 218, column: 5, scope: !414)
!420 = !DILocation(line: 218, column: 11, scope: !414)
!421 = !DILocation(line: 218, column: 4, scope: !414)
!422 = !DILocation(line: 219, column: 22, scope: !423)
!423 = distinct !DILexicalBlock(scope: !411, file: !1, line: 219, column: 7)
!424 = !DILocation(line: 219, column: 7, scope: !423)
!425 = !DILocation(line: 219, column: 42, scope: !423)
!426 = !DILocation(line: 219, column: 39, scope: !423)
!427 = !DILocation(line: 219, column: 7, scope: !411)
!428 = !DILocation(line: 220, column: 5, scope: !423)
!429 = !DILocation(line: 220, column: 11, scope: !423)
!430 = !DILocation(line: 220, column: 4, scope: !423)
!431 = !DILocation(line: 221, column: 2, scope: !411)
!432 = !DILocation(line: 222, column: 4, scope: !407)
!433 = !DILocation(line: 222, column: 10, scope: !407)
!434 = !DILocation(line: 223, column: 10, scope: !33)
!435 = !DILocation(line: 223, column: 2, scope: !33)
