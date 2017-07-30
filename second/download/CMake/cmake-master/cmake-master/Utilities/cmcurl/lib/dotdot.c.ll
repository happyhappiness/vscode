; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/dotdot.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_cstrdup = external global i8* (i8*)*, align 8
@Curl_cfree = external global void (i8*)*, align 8
@.str = private unnamed_addr constant [3 x i8] c"./\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"../\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"/./\00", align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"/.\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"/../\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"/..\00", align 1
@.str.6 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.7 = private unnamed_addr constant [3 x i8] c"..\00", align 1

; Function Attrs: nounwind uwtable
define i8* @Curl_dedotdotify(i8* %input) #0 !dbg !4 {
entry:
  %retval = alloca i8*, align 8
  %input.addr = alloca i8*, align 8
  %inlen = alloca i64, align 8
  %clone = alloca i8*, align 8
  %clen = alloca i64, align 8
  %out = alloca i8*, align 8
  %outptr = alloca i8*, align 8
  %orgclone = alloca i8*, align 8
  %queryp = alloca i8*, align 8
  %qlen = alloca i64, align 8
  %oindex = alloca i64, align 8
  store i8* %input, i8** %input.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %input.addr, metadata !14, metadata !15), !dbg !16
  call void @llvm.dbg.declare(metadata i64* %inlen, metadata !17, metadata !15), !dbg !21
  %0 = load i8*, i8** %input.addr, align 8, !dbg !22
  %call = call i64 @strlen(i8* %0) #4, !dbg !23
  store i64 %call, i64* %inlen, align 8, !dbg !21
  call void @llvm.dbg.declare(metadata i8** %clone, metadata !24, metadata !15), !dbg !25
  call void @llvm.dbg.declare(metadata i64* %clen, metadata !26, metadata !15), !dbg !27
  %1 = load i64, i64* %inlen, align 8, !dbg !28
  store i64 %1, i64* %clen, align 8, !dbg !27
  call void @llvm.dbg.declare(metadata i8** %out, metadata !29, metadata !15), !dbg !30
  %2 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !31
  %3 = load i64, i64* %inlen, align 8, !dbg !31
  %add = add i64 %3, 1, !dbg !31
  %call1 = call i8* %2(i64 %add), !dbg !31
  store i8* %call1, i8** %out, align 8, !dbg !30
  call void @llvm.dbg.declare(metadata i8** %outptr, metadata !32, metadata !15), !dbg !33
  call void @llvm.dbg.declare(metadata i8** %orgclone, metadata !34, metadata !15), !dbg !35
  call void @llvm.dbg.declare(metadata i8** %queryp, metadata !36, metadata !15), !dbg !37
  %4 = load i8*, i8** %out, align 8, !dbg !38
  %tobool = icmp ne i8* %4, null, !dbg !38
  br i1 %tobool, label %if.end, label %if.then, !dbg !40

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !41
  br label %return, !dbg !41

if.end:                                           ; preds = %entry
  %5 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !42
  %6 = load i8*, i8** %input.addr, align 8, !dbg !42
  %call2 = call i8* %5(i8* %6), !dbg !42
  store i8* %call2, i8** %clone, align 8, !dbg !43
  %7 = load i8*, i8** %clone, align 8, !dbg !44
  %tobool3 = icmp ne i8* %7, null, !dbg !44
  br i1 %tobool3, label %if.end5, label %if.then4, !dbg !46

if.then4:                                         ; preds = %if.end
  %8 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !47
  %9 = load i8*, i8** %out, align 8, !dbg !47
  call void %8(i8* %9), !dbg !47
  store i8* null, i8** %retval, align 8, !dbg !49
  br label %return, !dbg !49

if.end5:                                          ; preds = %if.end
  %10 = load i8*, i8** %clone, align 8, !dbg !50
  store i8* %10, i8** %orgclone, align 8, !dbg !51
  %11 = load i8*, i8** %out, align 8, !dbg !52
  store i8* %11, i8** %outptr, align 8, !dbg !53
  %12 = load i8*, i8** %clone, align 8, !dbg !54
  %13 = load i8, i8* %12, align 1, !dbg !56
  %tobool6 = icmp ne i8 %13, 0, !dbg !56
  br i1 %tobool6, label %if.end8, label %if.then7, !dbg !57

if.then7:                                         ; preds = %if.end5
  %14 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !58
  %15 = load i8*, i8** %out, align 8, !dbg !58
  call void %14(i8* %15), !dbg !58
  %16 = load i8*, i8** %clone, align 8, !dbg !60
  store i8* %16, i8** %retval, align 8, !dbg !61
  br label %return, !dbg !61

if.end8:                                          ; preds = %if.end5
  %17 = load i8*, i8** %clone, align 8, !dbg !62
  %call9 = call i8* @strchr(i8* %17, i32 63) #4, !dbg !63
  store i8* %call9, i8** %queryp, align 8, !dbg !64
  %18 = load i8*, i8** %queryp, align 8, !dbg !65
  %tobool10 = icmp ne i8* %18, null, !dbg !65
  br i1 %tobool10, label %if.then11, label %if.end12, !dbg !67

if.then11:                                        ; preds = %if.end8
  %19 = load i8*, i8** %queryp, align 8, !dbg !68
  store i8 0, i8* %19, align 1, !dbg !69
  br label %if.end12, !dbg !70

if.end12:                                         ; preds = %if.then11, %if.end8
  br label %do.body, !dbg !71

do.body:                                          ; preds = %do.cond83, %if.end12
  %20 = load i8*, i8** %clone, align 8, !dbg !72
  %call13 = call i32 @strncmp(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i8* %20, i64 2) #4, !dbg !75
  %tobool14 = icmp ne i32 %call13, 0, !dbg !75
  br i1 %tobool14, label %if.else, label %if.then15, !dbg !76

if.then15:                                        ; preds = %do.body
  %21 = load i8*, i8** %clone, align 8, !dbg !77
  %add.ptr = getelementptr inbounds i8, i8* %21, i64 2, !dbg !77
  store i8* %add.ptr, i8** %clone, align 8, !dbg !77
  %22 = load i64, i64* %clen, align 8, !dbg !79
  %sub = sub i64 %22, 2, !dbg !79
  store i64 %sub, i64* %clen, align 8, !dbg !79
  br label %if.end82, !dbg !80

if.else:                                          ; preds = %do.body
  %23 = load i8*, i8** %clone, align 8, !dbg !81
  %call16 = call i32 @strncmp(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8* %23, i64 3) #4, !dbg !83
  %tobool17 = icmp ne i32 %call16, 0, !dbg !83
  br i1 %tobool17, label %if.else21, label %if.then18, !dbg !84

if.then18:                                        ; preds = %if.else
  %24 = load i8*, i8** %clone, align 8, !dbg !85
  %add.ptr19 = getelementptr inbounds i8, i8* %24, i64 3, !dbg !85
  store i8* %add.ptr19, i8** %clone, align 8, !dbg !85
  %25 = load i64, i64* %clen, align 8, !dbg !87
  %sub20 = sub i64 %25, 3, !dbg !87
  store i64 %sub20, i64* %clen, align 8, !dbg !87
  br label %if.end81, !dbg !88

if.else21:                                        ; preds = %if.else
  %26 = load i8*, i8** %clone, align 8, !dbg !89
  %call22 = call i32 @strncmp(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8* %26, i64 3) #4, !dbg !91
  %tobool23 = icmp ne i32 %call22, 0, !dbg !91
  br i1 %tobool23, label %if.else27, label %if.then24, !dbg !92

if.then24:                                        ; preds = %if.else21
  %27 = load i8*, i8** %clone, align 8, !dbg !93
  %add.ptr25 = getelementptr inbounds i8, i8* %27, i64 2, !dbg !93
  store i8* %add.ptr25, i8** %clone, align 8, !dbg !93
  %28 = load i64, i64* %clen, align 8, !dbg !95
  %sub26 = sub i64 %28, 2, !dbg !95
  store i64 %sub26, i64* %clen, align 8, !dbg !95
  br label %if.end80, !dbg !96

if.else27:                                        ; preds = %if.else21
  %29 = load i8*, i8** %clone, align 8, !dbg !97
  %call28 = call i32 @strcmp(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0), i8* %29) #4, !dbg !99
  %tobool29 = icmp ne i32 %call28, 0, !dbg !99
  br i1 %tobool29, label %if.else32, label %if.then30, !dbg !100

if.then30:                                        ; preds = %if.else27
  %30 = load i8*, i8** %clone, align 8, !dbg !101
  %arrayidx = getelementptr inbounds i8, i8* %30, i64 1, !dbg !101
  store i8 47, i8* %arrayidx, align 1, !dbg !103
  %31 = load i8*, i8** %clone, align 8, !dbg !104
  %incdec.ptr = getelementptr inbounds i8, i8* %31, i32 1, !dbg !104
  store i8* %incdec.ptr, i8** %clone, align 8, !dbg !104
  %32 = load i64, i64* %clen, align 8, !dbg !105
  %sub31 = sub i64 %32, 1, !dbg !105
  store i64 %sub31, i64* %clen, align 8, !dbg !105
  br label %if.end79, !dbg !106

if.else32:                                        ; preds = %if.else27
  %33 = load i8*, i8** %clone, align 8, !dbg !107
  %call33 = call i32 @strncmp(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0), i8* %33, i64 4) #4, !dbg !109
  %tobool34 = icmp ne i32 %call33, 0, !dbg !109
  br i1 %tobool34, label %if.else43, label %if.then35, !dbg !110

if.then35:                                        ; preds = %if.else32
  %34 = load i8*, i8** %clone, align 8, !dbg !111
  %add.ptr36 = getelementptr inbounds i8, i8* %34, i64 3, !dbg !111
  store i8* %add.ptr36, i8** %clone, align 8, !dbg !111
  %35 = load i64, i64* %clen, align 8, !dbg !113
  %sub37 = sub i64 %35, 3, !dbg !113
  store i64 %sub37, i64* %clen, align 8, !dbg !113
  br label %while.cond, !dbg !114

while.cond:                                       ; preds = %if.end42, %if.then35
  %36 = load i8*, i8** %outptr, align 8, !dbg !115
  %37 = load i8*, i8** %out, align 8, !dbg !117
  %cmp = icmp ugt i8* %36, %37, !dbg !118
  br i1 %cmp, label %while.body, label %while.end, !dbg !119

while.body:                                       ; preds = %while.cond
  %38 = load i8*, i8** %outptr, align 8, !dbg !120
  %incdec.ptr38 = getelementptr inbounds i8, i8* %38, i32 -1, !dbg !120
  store i8* %incdec.ptr38, i8** %outptr, align 8, !dbg !120
  %39 = load i8*, i8** %outptr, align 8, !dbg !122
  %40 = load i8, i8* %39, align 1, !dbg !124
  %conv = sext i8 %40 to i32, !dbg !124
  %cmp39 = icmp eq i32 %conv, 47, !dbg !125
  br i1 %cmp39, label %if.then41, label %if.end42, !dbg !126

if.then41:                                        ; preds = %while.body
  br label %while.end, !dbg !127

if.end42:                                         ; preds = %while.body
  br label %while.cond, !dbg !128

while.end:                                        ; preds = %if.then41, %while.cond
  %41 = load i8*, i8** %outptr, align 8, !dbg !130
  store i8 0, i8* %41, align 1, !dbg !131
  br label %if.end78, !dbg !132

if.else43:                                        ; preds = %if.else32
  %42 = load i8*, i8** %clone, align 8, !dbg !133
  %call44 = call i32 @strcmp(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i8* %42) #4, !dbg !135
  %tobool45 = icmp ne i32 %call44, 0, !dbg !135
  br i1 %tobool45, label %if.else61, label %if.then46, !dbg !136

if.then46:                                        ; preds = %if.else43
  %43 = load i8*, i8** %clone, align 8, !dbg !137
  %arrayidx47 = getelementptr inbounds i8, i8* %43, i64 2, !dbg !137
  store i8 47, i8* %arrayidx47, align 1, !dbg !139
  %44 = load i8*, i8** %clone, align 8, !dbg !140
  %add.ptr48 = getelementptr inbounds i8, i8* %44, i64 2, !dbg !140
  store i8* %add.ptr48, i8** %clone, align 8, !dbg !140
  %45 = load i64, i64* %clen, align 8, !dbg !141
  %sub49 = sub i64 %45, 2, !dbg !141
  store i64 %sub49, i64* %clen, align 8, !dbg !141
  br label %while.cond50, !dbg !142

while.cond50:                                     ; preds = %if.end59, %if.then46
  %46 = load i8*, i8** %outptr, align 8, !dbg !143
  %47 = load i8*, i8** %out, align 8, !dbg !145
  %cmp51 = icmp ugt i8* %46, %47, !dbg !146
  br i1 %cmp51, label %while.body53, label %while.end60, !dbg !147

while.body53:                                     ; preds = %while.cond50
  %48 = load i8*, i8** %outptr, align 8, !dbg !148
  %incdec.ptr54 = getelementptr inbounds i8, i8* %48, i32 -1, !dbg !148
  store i8* %incdec.ptr54, i8** %outptr, align 8, !dbg !148
  %49 = load i8*, i8** %outptr, align 8, !dbg !150
  %50 = load i8, i8* %49, align 1, !dbg !152
  %conv55 = sext i8 %50 to i32, !dbg !152
  %cmp56 = icmp eq i32 %conv55, 47, !dbg !153
  br i1 %cmp56, label %if.then58, label %if.end59, !dbg !154

if.then58:                                        ; preds = %while.body53
  br label %while.end60, !dbg !155

if.end59:                                         ; preds = %while.body53
  br label %while.cond50, !dbg !156

while.end60:                                      ; preds = %if.then58, %while.cond50
  %51 = load i8*, i8** %outptr, align 8, !dbg !158
  store i8 0, i8* %51, align 1, !dbg !159
  br label %if.end77, !dbg !160

if.else61:                                        ; preds = %if.else43
  %52 = load i8*, i8** %clone, align 8, !dbg !161
  %call62 = call i32 @strcmp(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i32 0, i32 0), i8* %52) #4, !dbg !163
  %tobool63 = icmp ne i32 %call62, 0, !dbg !163
  br i1 %tobool63, label %lor.lhs.false, label %if.then66, !dbg !164

lor.lhs.false:                                    ; preds = %if.else61
  %53 = load i8*, i8** %clone, align 8, !dbg !165
  %call64 = call i32 @strcmp(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.7, i32 0, i32 0), i8* %53) #4, !dbg !167
  %tobool65 = icmp ne i32 %call64, 0, !dbg !167
  br i1 %tobool65, label %if.else67, label %if.then66, !dbg !168

if.then66:                                        ; preds = %lor.lhs.false, %if.else61
  %54 = load i8*, i8** %clone, align 8, !dbg !169
  store i8 0, i8* %54, align 1, !dbg !171
  br label %if.end76, !dbg !172

if.else67:                                        ; preds = %lor.lhs.false
  br label %do.body68, !dbg !173

do.body68:                                        ; preds = %land.end, %if.else67
  %55 = load i8*, i8** %clone, align 8, !dbg !175
  %incdec.ptr69 = getelementptr inbounds i8, i8* %55, i32 1, !dbg !175
  store i8* %incdec.ptr69, i8** %clone, align 8, !dbg !175
  %56 = load i8, i8* %55, align 1, !dbg !177
  %57 = load i8*, i8** %outptr, align 8, !dbg !178
  %incdec.ptr70 = getelementptr inbounds i8, i8* %57, i32 1, !dbg !178
  store i8* %incdec.ptr70, i8** %outptr, align 8, !dbg !178
  store i8 %56, i8* %57, align 1, !dbg !179
  %58 = load i64, i64* %clen, align 8, !dbg !180
  %dec = add i64 %58, -1, !dbg !180
  store i64 %dec, i64* %clen, align 8, !dbg !180
  br label %do.cond, !dbg !181

do.cond:                                          ; preds = %do.body68
  %59 = load i8*, i8** %clone, align 8, !dbg !182
  %60 = load i8, i8* %59, align 1, !dbg !184
  %conv71 = sext i8 %60 to i32, !dbg !184
  %tobool72 = icmp ne i32 %conv71, 0, !dbg !184
  br i1 %tobool72, label %land.rhs, label %land.end, !dbg !185

land.rhs:                                         ; preds = %do.cond
  %61 = load i8*, i8** %clone, align 8, !dbg !186
  %62 = load i8, i8* %61, align 1, !dbg !188
  %conv73 = sext i8 %62 to i32, !dbg !188
  %cmp74 = icmp ne i32 %conv73, 47, !dbg !189
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %63 = phi i1 [ false, %do.cond ], [ %cmp74, %land.rhs ]
  br i1 %63, label %do.body68, label %do.end, !dbg !190

do.end:                                           ; preds = %land.end
  %64 = load i8*, i8** %outptr, align 8, !dbg !192
  store i8 0, i8* %64, align 1, !dbg !193
  br label %if.end76

if.end76:                                         ; preds = %do.end, %if.then66
  br label %if.end77

if.end77:                                         ; preds = %if.end76, %while.end60
  br label %if.end78

if.end78:                                         ; preds = %if.end77, %while.end
  br label %if.end79

if.end79:                                         ; preds = %if.end78, %if.then30
  br label %if.end80

if.end80:                                         ; preds = %if.end79, %if.then24
  br label %if.end81

if.end81:                                         ; preds = %if.end80, %if.then18
  br label %if.end82

if.end82:                                         ; preds = %if.end81, %if.then15
  br label %do.cond83, !dbg !194

do.cond83:                                        ; preds = %if.end82
  %65 = load i8*, i8** %clone, align 8, !dbg !195
  %66 = load i8, i8* %65, align 1, !dbg !197
  %tobool84 = icmp ne i8 %66, 0, !dbg !198
  br i1 %tobool84, label %do.body, label %do.end85, !dbg !198

do.end85:                                         ; preds = %do.cond83
  %67 = load i8*, i8** %queryp, align 8, !dbg !199
  %tobool86 = icmp ne i8* %67, null, !dbg !199
  br i1 %tobool86, label %if.then87, label %if.end92, !dbg !201

if.then87:                                        ; preds = %do.end85
  call void @llvm.dbg.declare(metadata i64* %qlen, metadata !202, metadata !15), !dbg !204
  call void @llvm.dbg.declare(metadata i64* %oindex, metadata !205, metadata !15), !dbg !206
  %68 = load i8*, i8** %queryp, align 8, !dbg !207
  %69 = load i8*, i8** %orgclone, align 8, !dbg !208
  %sub.ptr.lhs.cast = ptrtoint i8* %68 to i64, !dbg !209
  %sub.ptr.rhs.cast = ptrtoint i8* %69 to i64, !dbg !209
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !209
  store i64 %sub.ptr.sub, i64* %oindex, align 8, !dbg !206
  %70 = load i64, i64* %oindex, align 8, !dbg !210
  %71 = load i8*, i8** %input.addr, align 8, !dbg !211
  %arrayidx88 = getelementptr inbounds i8, i8* %71, i64 %70, !dbg !211
  %call89 = call i64 @strlen(i8* %arrayidx88) #4, !dbg !212
  store i64 %call89, i64* %qlen, align 8, !dbg !213
  %72 = load i8*, i8** %outptr, align 8, !dbg !214
  %73 = load i64, i64* %oindex, align 8, !dbg !215
  %74 = load i8*, i8** %input.addr, align 8, !dbg !216
  %arrayidx90 = getelementptr inbounds i8, i8* %74, i64 %73, !dbg !216
  %75 = load i64, i64* %qlen, align 8, !dbg !217
  %add91 = add i64 %75, 1, !dbg !218
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %72, i8* %arrayidx90, i64 %add91, i32 1, i1 false), !dbg !219
  br label %if.end92, !dbg !220

if.end92:                                         ; preds = %if.then87, %do.end85
  %76 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !221
  %77 = load i8*, i8** %orgclone, align 8, !dbg !221
  call void %76(i8* %77), !dbg !221
  %78 = load i8*, i8** %out, align 8, !dbg !222
  store i8* %78, i8** %retval, align 8, !dbg !223
  br label %return, !dbg !223

return:                                           ; preds = %if.end92, %if.then7, %if.then4, %if.then
  %79 = load i8*, i8** %retval, align 8, !dbg !224
  ret i8* %79, !dbg !224
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #2

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!11, !12}
!llvm.ident = !{!13}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/dotdot.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "Curl_dedotdotify", scope: !1, file: !1, line: 53, type: !5, isLocal: false, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !8)
!11 = !{i32 2, !"Dwarf Version", i32 4}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!14 = !DILocalVariable(name: "input", arg: 1, scope: !4, file: !1, line: 53, type: !9)
!15 = !DIExpression()
!16 = !DILocation(line: 53, column: 36, scope: !4)
!17 = !DILocalVariable(name: "inlen", scope: !4, file: !1, line: 55, type: !18)
!18 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !19, line: 62, baseType: !20)
!19 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!20 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!21 = !DILocation(line: 55, column: 10, scope: !4)
!22 = !DILocation(line: 55, column: 25, scope: !4)
!23 = !DILocation(line: 55, column: 18, scope: !4)
!24 = !DILocalVariable(name: "clone", scope: !4, file: !1, line: 56, type: !7)
!25 = !DILocation(line: 56, column: 9, scope: !4)
!26 = !DILocalVariable(name: "clen", scope: !4, file: !1, line: 57, type: !18)
!27 = !DILocation(line: 57, column: 10, scope: !4)
!28 = !DILocation(line: 57, column: 17, scope: !4)
!29 = !DILocalVariable(name: "out", scope: !4, file: !1, line: 58, type: !7)
!30 = !DILocation(line: 58, column: 9, scope: !4)
!31 = !DILocation(line: 58, column: 15, scope: !4)
!32 = !DILocalVariable(name: "outptr", scope: !4, file: !1, line: 59, type: !7)
!33 = !DILocation(line: 59, column: 9, scope: !4)
!34 = !DILocalVariable(name: "orgclone", scope: !4, file: !1, line: 60, type: !7)
!35 = !DILocation(line: 60, column: 9, scope: !4)
!36 = !DILocalVariable(name: "queryp", scope: !4, file: !1, line: 61, type: !7)
!37 = !DILocation(line: 61, column: 9, scope: !4)
!38 = !DILocation(line: 62, column: 7, scope: !39)
!39 = distinct !DILexicalBlock(scope: !4, file: !1, line: 62, column: 6)
!40 = !DILocation(line: 62, column: 6, scope: !4)
!41 = !DILocation(line: 63, column: 5, scope: !39)
!42 = !DILocation(line: 66, column: 11, scope: !4)
!43 = !DILocation(line: 66, column: 9, scope: !4)
!44 = !DILocation(line: 67, column: 7, scope: !45)
!45 = distinct !DILexicalBlock(scope: !4, file: !1, line: 67, column: 6)
!46 = !DILocation(line: 67, column: 6, scope: !4)
!47 = !DILocation(line: 68, column: 5, scope: !48)
!48 = distinct !DILexicalBlock(scope: !45, file: !1, line: 67, column: 14)
!49 = !DILocation(line: 69, column: 5, scope: !48)
!50 = !DILocation(line: 71, column: 14, scope: !4)
!51 = !DILocation(line: 71, column: 12, scope: !4)
!52 = !DILocation(line: 72, column: 12, scope: !4)
!53 = !DILocation(line: 72, column: 10, scope: !4)
!54 = !DILocation(line: 74, column: 8, scope: !55)
!55 = distinct !DILexicalBlock(scope: !4, file: !1, line: 74, column: 6)
!56 = !DILocation(line: 74, column: 7, scope: !55)
!57 = !DILocation(line: 74, column: 6, scope: !4)
!58 = !DILocation(line: 76, column: 5, scope: !59)
!59 = distinct !DILexicalBlock(scope: !55, file: !1, line: 74, column: 15)
!60 = !DILocation(line: 77, column: 12, scope: !59)
!61 = !DILocation(line: 77, column: 5, scope: !59)
!62 = !DILocation(line: 85, column: 19, scope: !4)
!63 = !DILocation(line: 85, column: 12, scope: !4)
!64 = !DILocation(line: 85, column: 10, scope: !4)
!65 = !DILocation(line: 86, column: 6, scope: !66)
!66 = distinct !DILexicalBlock(scope: !4, file: !1, line: 86, column: 6)
!67 = !DILocation(line: 86, column: 6, scope: !4)
!68 = !DILocation(line: 87, column: 6, scope: !66)
!69 = !DILocation(line: 87, column: 13, scope: !66)
!70 = !DILocation(line: 87, column: 5, scope: !66)
!71 = !DILocation(line: 89, column: 3, scope: !4)
!72 = !DILocation(line: 94, column: 23, scope: !73)
!73 = distinct !DILexicalBlock(scope: !74, file: !1, line: 94, column: 8)
!74 = distinct !DILexicalBlock(scope: !4, file: !1, line: 89, column: 6)
!75 = !DILocation(line: 94, column: 9, scope: !73)
!76 = !DILocation(line: 94, column: 8, scope: !74)
!77 = !DILocation(line: 95, column: 12, scope: !78)
!78 = distinct !DILexicalBlock(scope: !73, file: !1, line: 94, column: 34)
!79 = !DILocation(line: 96, column: 11, scope: !78)
!80 = !DILocation(line: 97, column: 5, scope: !78)
!81 = !DILocation(line: 98, column: 29, scope: !82)
!82 = distinct !DILexicalBlock(scope: !73, file: !1, line: 98, column: 13)
!83 = !DILocation(line: 98, column: 14, scope: !82)
!84 = !DILocation(line: 98, column: 13, scope: !73)
!85 = !DILocation(line: 99, column: 12, scope: !86)
!86 = distinct !DILexicalBlock(scope: !82, file: !1, line: 98, column: 40)
!87 = !DILocation(line: 100, column: 11, scope: !86)
!88 = !DILocation(line: 101, column: 5, scope: !86)
!89 = !DILocation(line: 106, column: 29, scope: !90)
!90 = distinct !DILexicalBlock(scope: !82, file: !1, line: 106, column: 13)
!91 = !DILocation(line: 106, column: 14, scope: !90)
!92 = !DILocation(line: 106, column: 13, scope: !82)
!93 = !DILocation(line: 107, column: 12, scope: !94)
!94 = distinct !DILexicalBlock(scope: !90, file: !1, line: 106, column: 40)
!95 = !DILocation(line: 108, column: 11, scope: !94)
!96 = !DILocation(line: 109, column: 5, scope: !94)
!97 = !DILocation(line: 110, column: 27, scope: !98)
!98 = distinct !DILexicalBlock(scope: !90, file: !1, line: 110, column: 13)
!99 = !DILocation(line: 110, column: 14, scope: !98)
!100 = !DILocation(line: 110, column: 13, scope: !90)
!101 = !DILocation(line: 111, column: 7, scope: !102)
!102 = distinct !DILexicalBlock(scope: !98, file: !1, line: 110, column: 35)
!103 = !DILocation(line: 111, column: 15, scope: !102)
!104 = !DILocation(line: 112, column: 12, scope: !102)
!105 = !DILocation(line: 113, column: 11, scope: !102)
!106 = !DILocation(line: 114, column: 5, scope: !102)
!107 = !DILocation(line: 121, column: 30, scope: !108)
!108 = distinct !DILexicalBlock(scope: !98, file: !1, line: 121, column: 13)
!109 = !DILocation(line: 121, column: 14, scope: !108)
!110 = !DILocation(line: 121, column: 13, scope: !98)
!111 = !DILocation(line: 122, column: 12, scope: !112)
!112 = distinct !DILexicalBlock(scope: !108, file: !1, line: 121, column: 41)
!113 = !DILocation(line: 123, column: 11, scope: !112)
!114 = !DILocation(line: 125, column: 7, scope: !112)
!115 = !DILocation(line: 125, column: 13, scope: !116)
!116 = !DILexicalBlockFile(scope: !112, file: !1, discriminator: 1)
!117 = !DILocation(line: 125, column: 22, scope: !116)
!118 = !DILocation(line: 125, column: 20, scope: !116)
!119 = !DILocation(line: 125, column: 7, scope: !116)
!120 = !DILocation(line: 126, column: 15, scope: !121)
!121 = distinct !DILexicalBlock(scope: !112, file: !1, line: 125, column: 27)
!122 = !DILocation(line: 127, column: 13, scope: !123)
!123 = distinct !DILexicalBlock(scope: !121, file: !1, line: 127, column: 12)
!124 = !DILocation(line: 127, column: 12, scope: !123)
!125 = !DILocation(line: 127, column: 20, scope: !123)
!126 = !DILocation(line: 127, column: 12, scope: !121)
!127 = !DILocation(line: 128, column: 11, scope: !123)
!128 = !DILocation(line: 125, column: 7, scope: !129)
!129 = !DILexicalBlockFile(scope: !112, file: !1, discriminator: 2)
!130 = !DILocation(line: 130, column: 8, scope: !112)
!131 = !DILocation(line: 130, column: 15, scope: !112)
!132 = !DILocation(line: 131, column: 5, scope: !112)
!133 = !DILocation(line: 132, column: 28, scope: !134)
!134 = distinct !DILexicalBlock(scope: !108, file: !1, line: 132, column: 13)
!135 = !DILocation(line: 132, column: 14, scope: !134)
!136 = !DILocation(line: 132, column: 13, scope: !108)
!137 = !DILocation(line: 133, column: 7, scope: !138)
!138 = distinct !DILexicalBlock(scope: !134, file: !1, line: 132, column: 36)
!139 = !DILocation(line: 133, column: 15, scope: !138)
!140 = !DILocation(line: 134, column: 12, scope: !138)
!141 = !DILocation(line: 135, column: 11, scope: !138)
!142 = !DILocation(line: 137, column: 7, scope: !138)
!143 = !DILocation(line: 137, column: 13, scope: !144)
!144 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 1)
!145 = !DILocation(line: 137, column: 22, scope: !144)
!146 = !DILocation(line: 137, column: 20, scope: !144)
!147 = !DILocation(line: 137, column: 7, scope: !144)
!148 = !DILocation(line: 138, column: 15, scope: !149)
!149 = distinct !DILexicalBlock(scope: !138, file: !1, line: 137, column: 27)
!150 = !DILocation(line: 139, column: 13, scope: !151)
!151 = distinct !DILexicalBlock(scope: !149, file: !1, line: 139, column: 12)
!152 = !DILocation(line: 139, column: 12, scope: !151)
!153 = !DILocation(line: 139, column: 20, scope: !151)
!154 = !DILocation(line: 139, column: 12, scope: !149)
!155 = !DILocation(line: 140, column: 11, scope: !151)
!156 = !DILocation(line: 137, column: 7, scope: !157)
!157 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 2)
!158 = !DILocation(line: 142, column: 8, scope: !138)
!159 = !DILocation(line: 142, column: 15, scope: !138)
!160 = !DILocation(line: 143, column: 5, scope: !138)
!161 = !DILocation(line: 148, column: 26, scope: !162)
!162 = distinct !DILexicalBlock(scope: !134, file: !1, line: 148, column: 13)
!163 = !DILocation(line: 148, column: 14, scope: !162)
!164 = !DILocation(line: 148, column: 33, scope: !162)
!165 = !DILocation(line: 148, column: 50, scope: !166)
!166 = !DILexicalBlockFile(scope: !162, file: !1, discriminator: 1)
!167 = !DILocation(line: 148, column: 37, scope: !166)
!168 = !DILocation(line: 148, column: 13, scope: !166)
!169 = !DILocation(line: 149, column: 8, scope: !170)
!170 = distinct !DILexicalBlock(scope: !162, file: !1, line: 148, column: 58)
!171 = !DILocation(line: 149, column: 13, scope: !170)
!172 = !DILocation(line: 150, column: 5, scope: !170)
!173 = !DILocation(line: 158, column: 7, scope: !174)
!174 = distinct !DILexicalBlock(scope: !162, file: !1, line: 152, column: 10)
!175 = !DILocation(line: 159, column: 27, scope: !176)
!176 = distinct !DILexicalBlock(scope: !174, file: !1, line: 158, column: 10)
!177 = !DILocation(line: 159, column: 21, scope: !176)
!178 = !DILocation(line: 159, column: 16, scope: !176)
!179 = !DILocation(line: 159, column: 19, scope: !176)
!180 = !DILocation(line: 160, column: 13, scope: !176)
!181 = !DILocation(line: 161, column: 7, scope: !176)
!182 = !DILocation(line: 161, column: 16, scope: !183)
!183 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 1)
!184 = !DILocation(line: 161, column: 15, scope: !183)
!185 = !DILocation(line: 161, column: 22, scope: !183)
!186 = !DILocation(line: 161, column: 27, scope: !187)
!187 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 2)
!188 = !DILocation(line: 161, column: 26, scope: !187)
!189 = !DILocation(line: 161, column: 33, scope: !187)
!190 = !DILocation(line: 161, column: 7, scope: !191)
!191 = !DILexicalBlockFile(scope: !176, file: !1, discriminator: 3)
!192 = !DILocation(line: 162, column: 8, scope: !174)
!193 = !DILocation(line: 162, column: 15, scope: !174)
!194 = !DILocation(line: 165, column: 3, scope: !74)
!195 = !DILocation(line: 165, column: 12, scope: !196)
!196 = !DILexicalBlockFile(scope: !4, file: !1, discriminator: 1)
!197 = !DILocation(line: 165, column: 11, scope: !196)
!198 = !DILocation(line: 165, column: 3, scope: !196)
!199 = !DILocation(line: 167, column: 6, scope: !200)
!200 = distinct !DILexicalBlock(scope: !4, file: !1, line: 167, column: 6)
!201 = !DILocation(line: 167, column: 6, scope: !4)
!202 = !DILocalVariable(name: "qlen", scope: !203, file: !1, line: 168, type: !18)
!203 = distinct !DILexicalBlock(scope: !200, file: !1, line: 167, column: 14)
!204 = !DILocation(line: 168, column: 12, scope: !203)
!205 = !DILocalVariable(name: "oindex", scope: !203, file: !1, line: 172, type: !18)
!206 = !DILocation(line: 172, column: 12, scope: !203)
!207 = !DILocation(line: 172, column: 21, scope: !203)
!208 = !DILocation(line: 172, column: 30, scope: !203)
!209 = !DILocation(line: 172, column: 28, scope: !203)
!210 = !DILocation(line: 173, column: 26, scope: !203)
!211 = !DILocation(line: 173, column: 20, scope: !203)
!212 = !DILocation(line: 173, column: 12, scope: !203)
!213 = !DILocation(line: 173, column: 10, scope: !203)
!214 = !DILocation(line: 174, column: 12, scope: !203)
!215 = !DILocation(line: 174, column: 27, scope: !203)
!216 = !DILocation(line: 174, column: 21, scope: !203)
!217 = !DILocation(line: 174, column: 36, scope: !203)
!218 = !DILocation(line: 174, column: 40, scope: !203)
!219 = !DILocation(line: 174, column: 5, scope: !203)
!220 = !DILocation(line: 175, column: 3, scope: !203)
!221 = !DILocation(line: 177, column: 3, scope: !4)
!222 = !DILocation(line: 178, column: 10, scope: !4)
!223 = !DILocation(line: 178, column: 3, scope: !4)
!224 = !DILocation(line: 179, column: 1, scope: !4)
