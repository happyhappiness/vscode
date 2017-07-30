; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hmac.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.HMAC_context = type { %struct.HMAC_params*, i8*, i8* }
%struct.HMAC_params = type { void (i8*)*, void (i8*, i8*, i32)*, void (i8*, i8*)*, i32, i32, i32 }

@Curl_cmalloc = external global i8* (i64)*, align 8
@hmac_ipad = internal constant i8 54, align 1
@hmac_opad = internal constant i8 92, align 1
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define %struct.HMAC_context* @Curl_HMAC_init(%struct.HMAC_params* %hashparams, i8* %key, i32 %keylen) #0 !dbg !10 {
entry:
  %retval = alloca %struct.HMAC_context*, align 8
  %hashparams.addr = alloca %struct.HMAC_params*, align 8
  %key.addr = alloca i8*, align 8
  %keylen.addr = alloca i32, align 4
  %i = alloca i64, align 8
  %ctxt = alloca %struct.HMAC_context*, align 8
  %hkey = alloca i8*, align 8
  %b = alloca i8, align 1
  store %struct.HMAC_params* %hashparams, %struct.HMAC_params** %hashparams.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.HMAC_params** %hashparams.addr, metadata !62, metadata !63), !dbg !64
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !65, metadata !63), !dbg !66
  store i32 %keylen, i32* %keylen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %keylen.addr, metadata !67, metadata !63), !dbg !68
  call void @llvm.dbg.declare(metadata i64* %i, metadata !69, metadata !63), !dbg !73
  call void @llvm.dbg.declare(metadata %struct.HMAC_context** %ctxt, metadata !74, metadata !63), !dbg !75
  call void @llvm.dbg.declare(metadata i8** %hkey, metadata !76, metadata !63), !dbg !77
  call void @llvm.dbg.declare(metadata i8* %b, metadata !78, metadata !63), !dbg !79
  %0 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !80
  %hmac_ctxtsize = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %0, i32 0, i32 3, !dbg !81
  %1 = load i32, i32* %hmac_ctxtsize, align 8, !dbg !81
  %mul = mul i32 2, %1, !dbg !82
  %conv = zext i32 %mul to i64, !dbg !83
  %add = add i64 24, %conv, !dbg !84
  %2 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !85
  %hmac_resultlen = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %2, i32 0, i32 5, !dbg !86
  %3 = load i32, i32* %hmac_resultlen, align 8, !dbg !86
  %conv1 = zext i32 %3 to i64, !dbg !85
  %add2 = add i64 %add, %conv1, !dbg !87
  store i64 %add2, i64* %i, align 8, !dbg !88
  %4 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !89
  %5 = load i64, i64* %i, align 8, !dbg !89
  %call = call i8* %4(i64 %5), !dbg !89
  %6 = bitcast i8* %call to %struct.HMAC_context*, !dbg !89
  store %struct.HMAC_context* %6, %struct.HMAC_context** %ctxt, align 8, !dbg !90
  %7 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !91
  %tobool = icmp ne %struct.HMAC_context* %7, null, !dbg !91
  br i1 %tobool, label %if.end, label %if.then, !dbg !93

if.then:                                          ; preds = %entry
  %8 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !94
  store %struct.HMAC_context* %8, %struct.HMAC_context** %retval, align 8, !dbg !95
  br label %return, !dbg !95

if.end:                                           ; preds = %entry
  %9 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !96
  %10 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !97
  %hmac_hash = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %10, i32 0, i32 0, !dbg !98
  store %struct.HMAC_params* %9, %struct.HMAC_params** %hmac_hash, align 8, !dbg !99
  %11 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !100
  %add.ptr = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %11, i64 1, !dbg !101
  %12 = bitcast %struct.HMAC_context* %add.ptr to i8*, !dbg !102
  %13 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !103
  %hmac_hashctxt1 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %13, i32 0, i32 1, !dbg !104
  store i8* %12, i8** %hmac_hashctxt1, align 8, !dbg !105
  %14 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !106
  %hmac_hashctxt13 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %14, i32 0, i32 1, !dbg !107
  %15 = load i8*, i8** %hmac_hashctxt13, align 8, !dbg !107
  %16 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !108
  %hmac_ctxtsize4 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %16, i32 0, i32 3, !dbg !109
  %17 = load i32, i32* %hmac_ctxtsize4, align 8, !dbg !109
  %idx.ext = zext i32 %17 to i64, !dbg !110
  %add.ptr5 = getelementptr inbounds i8, i8* %15, i64 %idx.ext, !dbg !110
  %18 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !111
  %hmac_hashctxt2 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %18, i32 0, i32 2, !dbg !112
  store i8* %add.ptr5, i8** %hmac_hashctxt2, align 8, !dbg !113
  %19 = load i32, i32* %keylen.addr, align 4, !dbg !114
  %20 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !116
  %hmac_maxkeylen = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %20, i32 0, i32 4, !dbg !117
  %21 = load i32, i32* %hmac_maxkeylen, align 4, !dbg !117
  %cmp = icmp ugt i32 %19, %21, !dbg !118
  br i1 %cmp, label %if.then7, label %if.end16, !dbg !119

if.then7:                                         ; preds = %if.end
  %22 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !120
  %hmac_hinit = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %22, i32 0, i32 0, !dbg !122
  %23 = load void (i8*)*, void (i8*)** %hmac_hinit, align 8, !dbg !122
  %24 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !123
  %hmac_hashctxt18 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %24, i32 0, i32 1, !dbg !124
  %25 = load i8*, i8** %hmac_hashctxt18, align 8, !dbg !124
  call void %23(i8* %25), !dbg !125
  %26 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !126
  %hmac_hupdate = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %26, i32 0, i32 1, !dbg !127
  %27 = load void (i8*, i8*, i32)*, void (i8*, i8*, i32)** %hmac_hupdate, align 8, !dbg !127
  %28 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !128
  %hmac_hashctxt19 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %28, i32 0, i32 1, !dbg !129
  %29 = load i8*, i8** %hmac_hashctxt19, align 8, !dbg !129
  %30 = load i8*, i8** %key.addr, align 8, !dbg !130
  %31 = load i32, i32* %keylen.addr, align 4, !dbg !131
  call void %27(i8* %29, i8* %30, i32 %31), !dbg !132
  %32 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !133
  %hmac_hashctxt210 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %32, i32 0, i32 2, !dbg !134
  %33 = load i8*, i8** %hmac_hashctxt210, align 8, !dbg !134
  %34 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !135
  %hmac_ctxtsize11 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %34, i32 0, i32 3, !dbg !136
  %35 = load i32, i32* %hmac_ctxtsize11, align 8, !dbg !136
  %idx.ext12 = zext i32 %35 to i64, !dbg !137
  %add.ptr13 = getelementptr inbounds i8, i8* %33, i64 %idx.ext12, !dbg !137
  store i8* %add.ptr13, i8** %hkey, align 8, !dbg !138
  %36 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !139
  %hmac_hfinal = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %36, i32 0, i32 2, !dbg !140
  %37 = load void (i8*, i8*)*, void (i8*, i8*)** %hmac_hfinal, align 8, !dbg !140
  %38 = load i8*, i8** %hkey, align 8, !dbg !141
  %39 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !142
  %hmac_hashctxt114 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %39, i32 0, i32 1, !dbg !143
  %40 = load i8*, i8** %hmac_hashctxt114, align 8, !dbg !143
  call void %37(i8* %38, i8* %40), !dbg !144
  %41 = load i8*, i8** %hkey, align 8, !dbg !145
  store i8* %41, i8** %key.addr, align 8, !dbg !146
  %42 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !147
  %hmac_resultlen15 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %42, i32 0, i32 5, !dbg !148
  %43 = load i32, i32* %hmac_resultlen15, align 8, !dbg !148
  store i32 %43, i32* %keylen.addr, align 4, !dbg !149
  br label %if.end16, !dbg !150

if.end16:                                         ; preds = %if.then7, %if.end
  %44 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !151
  %hmac_hinit17 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %44, i32 0, i32 0, !dbg !152
  %45 = load void (i8*)*, void (i8*)** %hmac_hinit17, align 8, !dbg !152
  %46 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !153
  %hmac_hashctxt118 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %46, i32 0, i32 1, !dbg !154
  %47 = load i8*, i8** %hmac_hashctxt118, align 8, !dbg !154
  call void %45(i8* %47), !dbg !155
  %48 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !156
  %hmac_hinit19 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %48, i32 0, i32 0, !dbg !157
  %49 = load void (i8*)*, void (i8*)** %hmac_hinit19, align 8, !dbg !157
  %50 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !158
  %hmac_hashctxt220 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %50, i32 0, i32 2, !dbg !159
  %51 = load i8*, i8** %hmac_hashctxt220, align 8, !dbg !159
  call void %49(i8* %51), !dbg !160
  store i64 0, i64* %i, align 8, !dbg !161
  br label %for.cond, !dbg !163

for.cond:                                         ; preds = %for.inc, %if.end16
  %52 = load i64, i64* %i, align 8, !dbg !164
  %53 = load i32, i32* %keylen.addr, align 4, !dbg !167
  %conv21 = zext i32 %53 to i64, !dbg !167
  %cmp22 = icmp ult i64 %52, %conv21, !dbg !168
  br i1 %cmp22, label %for.body, label %for.end, !dbg !169

for.body:                                         ; preds = %for.cond
  %54 = load i8*, i8** %key.addr, align 8, !dbg !170
  %55 = load i8, i8* %54, align 1, !dbg !172
  %conv24 = zext i8 %55 to i32, !dbg !172
  %xor = xor i32 %conv24, 54, !dbg !173
  %conv25 = trunc i32 %xor to i8, !dbg !174
  store i8 %conv25, i8* %b, align 1, !dbg !175
  %56 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !176
  %hmac_hupdate26 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %56, i32 0, i32 1, !dbg !177
  %57 = load void (i8*, i8*, i32)*, void (i8*, i8*, i32)** %hmac_hupdate26, align 8, !dbg !177
  %58 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !178
  %hmac_hashctxt127 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %58, i32 0, i32 1, !dbg !179
  %59 = load i8*, i8** %hmac_hashctxt127, align 8, !dbg !179
  call void %57(i8* %59, i8* %b, i32 1), !dbg !180
  %60 = load i8*, i8** %key.addr, align 8, !dbg !181
  %incdec.ptr = getelementptr inbounds i8, i8* %60, i32 1, !dbg !181
  store i8* %incdec.ptr, i8** %key.addr, align 8, !dbg !181
  %61 = load i8, i8* %60, align 1, !dbg !182
  %conv28 = zext i8 %61 to i32, !dbg !182
  %xor29 = xor i32 %conv28, 92, !dbg !183
  %conv30 = trunc i32 %xor29 to i8, !dbg !184
  store i8 %conv30, i8* %b, align 1, !dbg !185
  %62 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !186
  %hmac_hupdate31 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %62, i32 0, i32 1, !dbg !187
  %63 = load void (i8*, i8*, i32)*, void (i8*, i8*, i32)** %hmac_hupdate31, align 8, !dbg !187
  %64 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !188
  %hmac_hashctxt232 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %64, i32 0, i32 2, !dbg !189
  %65 = load i8*, i8** %hmac_hashctxt232, align 8, !dbg !189
  call void %63(i8* %65, i8* %b, i32 1), !dbg !190
  br label %for.inc, !dbg !191

for.inc:                                          ; preds = %for.body
  %66 = load i64, i64* %i, align 8, !dbg !192
  %inc = add i64 %66, 1, !dbg !192
  store i64 %inc, i64* %i, align 8, !dbg !192
  br label %for.cond, !dbg !194

for.end:                                          ; preds = %for.cond
  br label %for.cond33, !dbg !195

for.cond33:                                       ; preds = %for.inc43, %for.end
  %67 = load i64, i64* %i, align 8, !dbg !196
  %68 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !200
  %hmac_maxkeylen34 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %68, i32 0, i32 4, !dbg !201
  %69 = load i32, i32* %hmac_maxkeylen34, align 4, !dbg !201
  %conv35 = zext i32 %69 to i64, !dbg !200
  %cmp36 = icmp ult i64 %67, %conv35, !dbg !202
  br i1 %cmp36, label %for.body38, label %for.end45, !dbg !203

for.body38:                                       ; preds = %for.cond33
  %70 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !204
  %hmac_hupdate39 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %70, i32 0, i32 1, !dbg !206
  %71 = load void (i8*, i8*, i32)*, void (i8*, i8*, i32)** %hmac_hupdate39, align 8, !dbg !206
  %72 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !207
  %hmac_hashctxt140 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %72, i32 0, i32 1, !dbg !208
  %73 = load i8*, i8** %hmac_hashctxt140, align 8, !dbg !208
  call void %71(i8* %73, i8* @hmac_ipad, i32 1), !dbg !209
  %74 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams.addr, align 8, !dbg !210
  %hmac_hupdate41 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %74, i32 0, i32 1, !dbg !211
  %75 = load void (i8*, i8*, i32)*, void (i8*, i8*, i32)** %hmac_hupdate41, align 8, !dbg !211
  %76 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !212
  %hmac_hashctxt242 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %76, i32 0, i32 2, !dbg !213
  %77 = load i8*, i8** %hmac_hashctxt242, align 8, !dbg !213
  call void %75(i8* %77, i8* @hmac_opad, i32 1), !dbg !214
  br label %for.inc43, !dbg !215

for.inc43:                                        ; preds = %for.body38
  %78 = load i64, i64* %i, align 8, !dbg !216
  %inc44 = add i64 %78, 1, !dbg !216
  store i64 %inc44, i64* %i, align 8, !dbg !216
  br label %for.cond33, !dbg !218

for.end45:                                        ; preds = %for.cond33
  %79 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt, align 8, !dbg !219
  store %struct.HMAC_context* %79, %struct.HMAC_context** %retval, align 8, !dbg !220
  br label %return, !dbg !220

return:                                           ; preds = %for.end45, %if.then
  %80 = load %struct.HMAC_context*, %struct.HMAC_context** %retval, align 8, !dbg !221
  ret %struct.HMAC_context* %80, !dbg !221
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @Curl_HMAC_update(%struct.HMAC_context* %ctxt, i8* %data, i32 %len) #0 !dbg !47 {
entry:
  %ctxt.addr = alloca %struct.HMAC_context*, align 8
  %data.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  store %struct.HMAC_context* %ctxt, %struct.HMAC_context** %ctxt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.HMAC_context** %ctxt.addr, metadata !222, metadata !63), !dbg !223
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !224, metadata !63), !dbg !225
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !226, metadata !63), !dbg !227
  %0 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !228
  %hmac_hash = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %0, i32 0, i32 0, !dbg !229
  %1 = load %struct.HMAC_params*, %struct.HMAC_params** %hmac_hash, align 8, !dbg !229
  %hmac_hupdate = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %1, i32 0, i32 1, !dbg !230
  %2 = load void (i8*, i8*, i32)*, void (i8*, i8*, i32)** %hmac_hupdate, align 8, !dbg !230
  %3 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !231
  %hmac_hashctxt1 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %3, i32 0, i32 1, !dbg !232
  %4 = load i8*, i8** %hmac_hashctxt1, align 8, !dbg !232
  %5 = load i8*, i8** %data.addr, align 8, !dbg !233
  %6 = load i32, i32* %len.addr, align 4, !dbg !234
  call void %2(i8* %4, i8* %5, i32 %6), !dbg !235
  ret i32 0, !dbg !236
}

; Function Attrs: nounwind uwtable
define i32 @Curl_HMAC_final(%struct.HMAC_context* %ctxt, i8* %result) #0 !dbg !51 {
entry:
  %ctxt.addr = alloca %struct.HMAC_context*, align 8
  %result.addr = alloca i8*, align 8
  %hashparams = alloca %struct.HMAC_params*, align 8
  store %struct.HMAC_context* %ctxt, %struct.HMAC_context** %ctxt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.HMAC_context** %ctxt.addr, metadata !237, metadata !63), !dbg !238
  store i8* %result, i8** %result.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %result.addr, metadata !239, metadata !63), !dbg !240
  call void @llvm.dbg.declare(metadata %struct.HMAC_params** %hashparams, metadata !241, metadata !63), !dbg !242
  %0 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !243
  %hmac_hash = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %0, i32 0, i32 0, !dbg !244
  %1 = load %struct.HMAC_params*, %struct.HMAC_params** %hmac_hash, align 8, !dbg !244
  store %struct.HMAC_params* %1, %struct.HMAC_params** %hashparams, align 8, !dbg !242
  %2 = load i8*, i8** %result.addr, align 8, !dbg !245
  %tobool = icmp ne i8* %2, null, !dbg !245
  br i1 %tobool, label %if.end, label %if.then, !dbg !247

if.then:                                          ; preds = %entry
  %3 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !248
  %hmac_hashctxt2 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %3, i32 0, i32 2, !dbg !249
  %4 = load i8*, i8** %hmac_hashctxt2, align 8, !dbg !249
  %5 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !250
  %hmac_hash1 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %5, i32 0, i32 0, !dbg !251
  %6 = load %struct.HMAC_params*, %struct.HMAC_params** %hmac_hash1, align 8, !dbg !251
  %hmac_ctxtsize = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %6, i32 0, i32 3, !dbg !252
  %7 = load i32, i32* %hmac_ctxtsize, align 8, !dbg !252
  %idx.ext = zext i32 %7 to i64, !dbg !253
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 %idx.ext, !dbg !253
  store i8* %add.ptr, i8** %result.addr, align 8, !dbg !254
  br label %if.end, !dbg !255

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams, align 8, !dbg !256
  %hmac_hfinal = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %8, i32 0, i32 2, !dbg !257
  %9 = load void (i8*, i8*)*, void (i8*, i8*)** %hmac_hfinal, align 8, !dbg !257
  %10 = load i8*, i8** %result.addr, align 8, !dbg !258
  %11 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !259
  %hmac_hashctxt1 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %11, i32 0, i32 1, !dbg !260
  %12 = load i8*, i8** %hmac_hashctxt1, align 8, !dbg !260
  call void %9(i8* %10, i8* %12), !dbg !261
  %13 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams, align 8, !dbg !262
  %hmac_hupdate = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %13, i32 0, i32 1, !dbg !263
  %14 = load void (i8*, i8*, i32)*, void (i8*, i8*, i32)** %hmac_hupdate, align 8, !dbg !263
  %15 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !264
  %hmac_hashctxt22 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %15, i32 0, i32 2, !dbg !265
  %16 = load i8*, i8** %hmac_hashctxt22, align 8, !dbg !265
  %17 = load i8*, i8** %result.addr, align 8, !dbg !266
  %18 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams, align 8, !dbg !267
  %hmac_resultlen = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %18, i32 0, i32 5, !dbg !268
  %19 = load i32, i32* %hmac_resultlen, align 8, !dbg !268
  call void %14(i8* %16, i8* %17, i32 %19), !dbg !269
  %20 = load %struct.HMAC_params*, %struct.HMAC_params** %hashparams, align 8, !dbg !270
  %hmac_hfinal3 = getelementptr inbounds %struct.HMAC_params, %struct.HMAC_params* %20, i32 0, i32 2, !dbg !271
  %21 = load void (i8*, i8*)*, void (i8*, i8*)** %hmac_hfinal3, align 8, !dbg !271
  %22 = load i8*, i8** %result.addr, align 8, !dbg !272
  %23 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !273
  %hmac_hashctxt24 = getelementptr inbounds %struct.HMAC_context, %struct.HMAC_context* %23, i32 0, i32 2, !dbg !274
  %24 = load i8*, i8** %hmac_hashctxt24, align 8, !dbg !274
  call void %21(i8* %22, i8* %24), !dbg !275
  %25 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !276
  %26 = load %struct.HMAC_context*, %struct.HMAC_context** %ctxt.addr, align 8, !dbg !276
  %27 = bitcast %struct.HMAC_context* %26 to i8*, !dbg !276
  call void %25(i8* %27), !dbg !276
  ret i32 0, !dbg !277
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!59, !60}
!llvm.ident = !{!61}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !9, globals: !54)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hmac.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !5, !7, !8}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!9 = !{!10, !47, !51}
!10 = distinct !DISubprogram(name: "Curl_HMAC_init", scope: !1, file: !1, line: 51, type: !11, isLocal: false, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !19, !34, !36}
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "HMAC_context", file: !15, line: 52, baseType: !16)
!15 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_hmac.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!16 = !DICompositeType(tag: DW_TAG_structure_type, file: !15, line: 48, size: 192, align: 64, elements: !17)
!17 = !{!18, !45, !46}
!18 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_hash", scope: !16, file: !15, line: 49, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !21)
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "HMAC_params", file: !15, line: 43, baseType: !22)
!22 = !DICompositeType(tag: DW_TAG_structure_type, file: !15, line: 36, size: 320, align: 64, elements: !23)
!23 = !{!24, !29, !37, !42, !43, !44}
!24 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_hinit", scope: !22, file: !15, line: 37, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "HMAC_hinit_func", file: !15, line: 27, baseType: !26)
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!27 = !DISubroutineType(types: !28)
!28 = !{null, !4}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_hupdate", scope: !22, file: !15, line: 38, baseType: !30, size: 64, align: 64, offset: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "HMAC_hupdate_func", file: !15, line: 28, baseType: !31)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DISubroutineType(types: !33)
!33 = !{null, !4, !34, !36}
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !8)
!36 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_hfinal", scope: !22, file: !15, line: 39, baseType: !38, size: 64, align: 64, offset: 128)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "HMAC_hfinal_func", file: !15, line: 31, baseType: !39)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DISubroutineType(types: !41)
!41 = !{null, !7, !4}
!42 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_ctxtsize", scope: !22, file: !15, line: 40, baseType: !36, size: 32, align: 32, offset: 192)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_maxkeylen", scope: !22, file: !15, line: 41, baseType: !36, size: 32, align: 32, offset: 224)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_resultlen", scope: !22, file: !15, line: 42, baseType: !36, size: 32, align: 32, offset: 256)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_hashctxt1", scope: !16, file: !15, line: 50, baseType: !4, size: 64, align: 64, offset: 64)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "hmac_hashctxt2", scope: !16, file: !15, line: 51, baseType: !4, size: 64, align: 64, offset: 128)
!47 = distinct !DISubprogram(name: "Curl_HMAC_update", scope: !1, file: !1, line: 103, type: !48, isLocal: false, isDefinition: true, scopeLine: 106, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!48 = !DISubroutineType(types: !49)
!49 = !{!50, !13, !34, !36}
!50 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!51 = distinct !DISubprogram(name: "Curl_HMAC_final", scope: !1, file: !1, line: 113, type: !52, isLocal: false, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!52 = !DISubroutineType(types: !53)
!53 = !{!50, !13, !7}
!54 = !{!55, !56, !57, !58}
!55 = !DIGlobalVariable(name: "hmac_ipad", scope: !0, file: !1, line: 45, type: !35, isLocal: true, isDefinition: true, variable: i8 54)
!56 = !DIGlobalVariable(name: "hmac_opad", scope: !0, file: !1, line: 46, type: !35, isLocal: true, isDefinition: true, variable: i8 92)
!57 = !DIGlobalVariable(name: "hmac_ipad", scope: !0, file: !1, line: 45, type: !35, isLocal: true, isDefinition: true, variable: i8* @hmac_ipad)
!58 = !DIGlobalVariable(name: "hmac_opad", scope: !0, file: !1, line: 46, type: !35, isLocal: true, isDefinition: true, variable: i8* @hmac_opad)
!59 = !{i32 2, !"Dwarf Version", i32 4}
!60 = !{i32 2, !"Debug Info Version", i32 3}
!61 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!62 = !DILocalVariable(name: "hashparams", arg: 1, scope: !10, file: !1, line: 51, type: !19)
!63 = !DIExpression()
!64 = !DILocation(line: 51, column: 36, scope: !10)
!65 = !DILocalVariable(name: "key", arg: 2, scope: !10, file: !1, line: 52, type: !34)
!66 = !DILocation(line: 52, column: 37, scope: !10)
!67 = !DILocalVariable(name: "keylen", arg: 3, scope: !10, file: !1, line: 53, type: !36)
!68 = !DILocation(line: 53, column: 29, scope: !10)
!69 = !DILocalVariable(name: "i", scope: !10, file: !1, line: 55, type: !70)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !71, line: 62, baseType: !72)
!71 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!72 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!73 = !DILocation(line: 55, column: 10, scope: !10)
!74 = !DILocalVariable(name: "ctxt", scope: !10, file: !1, line: 56, type: !13)
!75 = !DILocation(line: 56, column: 17, scope: !10)
!76 = !DILocalVariable(name: "hkey", scope: !10, file: !1, line: 57, type: !7)
!77 = !DILocation(line: 57, column: 18, scope: !10)
!78 = !DILocalVariable(name: "b", scope: !10, file: !1, line: 58, type: !8)
!79 = !DILocation(line: 58, column: 17, scope: !10)
!80 = !DILocation(line: 61, column: 26, scope: !10)
!81 = !DILocation(line: 61, column: 38, scope: !10)
!82 = !DILocation(line: 61, column: 24, scope: !10)
!83 = !DILocation(line: 61, column: 22, scope: !10)
!84 = !DILocation(line: 61, column: 20, scope: !10)
!85 = !DILocation(line: 62, column: 5, scope: !10)
!86 = !DILocation(line: 62, column: 17, scope: !10)
!87 = !DILocation(line: 61, column: 52, scope: !10)
!88 = !DILocation(line: 61, column: 5, scope: !10)
!89 = !DILocation(line: 63, column: 10, scope: !10)
!90 = !DILocation(line: 63, column: 8, scope: !10)
!91 = !DILocation(line: 65, column: 7, scope: !92)
!92 = distinct !DILexicalBlock(scope: !10, file: !1, line: 65, column: 6)
!93 = !DILocation(line: 65, column: 6, scope: !10)
!94 = !DILocation(line: 66, column: 12, scope: !92)
!95 = !DILocation(line: 66, column: 5, scope: !92)
!96 = !DILocation(line: 68, column: 21, scope: !10)
!97 = !DILocation(line: 68, column: 3, scope: !10)
!98 = !DILocation(line: 68, column: 9, scope: !10)
!99 = !DILocation(line: 68, column: 19, scope: !10)
!100 = !DILocation(line: 69, column: 36, scope: !10)
!101 = !DILocation(line: 69, column: 41, scope: !10)
!102 = !DILocation(line: 69, column: 26, scope: !10)
!103 = !DILocation(line: 69, column: 3, scope: !10)
!104 = !DILocation(line: 69, column: 9, scope: !10)
!105 = !DILocation(line: 69, column: 24, scope: !10)
!106 = !DILocation(line: 70, column: 45, scope: !10)
!107 = !DILocation(line: 70, column: 51, scope: !10)
!108 = !DILocation(line: 71, column: 7, scope: !10)
!109 = !DILocation(line: 71, column: 19, scope: !10)
!110 = !DILocation(line: 70, column: 66, scope: !10)
!111 = !DILocation(line: 70, column: 3, scope: !10)
!112 = !DILocation(line: 70, column: 9, scope: !10)
!113 = !DILocation(line: 70, column: 24, scope: !10)
!114 = !DILocation(line: 74, column: 6, scope: !115)
!115 = distinct !DILexicalBlock(scope: !10, file: !1, line: 74, column: 6)
!116 = !DILocation(line: 74, column: 15, scope: !115)
!117 = !DILocation(line: 74, column: 27, scope: !115)
!118 = !DILocation(line: 74, column: 13, scope: !115)
!119 = !DILocation(line: 74, column: 6, scope: !10)
!120 = !DILocation(line: 75, column: 7, scope: !121)
!121 = distinct !DILexicalBlock(scope: !115, file: !1, line: 74, column: 43)
!122 = !DILocation(line: 75, column: 19, scope: !121)
!123 = !DILocation(line: 75, column: 31, scope: !121)
!124 = !DILocation(line: 75, column: 37, scope: !121)
!125 = !DILocation(line: 75, column: 5, scope: !121)
!126 = !DILocation(line: 76, column: 7, scope: !121)
!127 = !DILocation(line: 76, column: 19, scope: !121)
!128 = !DILocation(line: 76, column: 33, scope: !121)
!129 = !DILocation(line: 76, column: 39, scope: !121)
!130 = !DILocation(line: 76, column: 55, scope: !121)
!131 = !DILocation(line: 76, column: 60, scope: !121)
!132 = !DILocation(line: 76, column: 5, scope: !121)
!133 = !DILocation(line: 77, column: 30, scope: !121)
!134 = !DILocation(line: 77, column: 36, scope: !121)
!135 = !DILocation(line: 77, column: 53, scope: !121)
!136 = !DILocation(line: 77, column: 65, scope: !121)
!137 = !DILocation(line: 77, column: 51, scope: !121)
!138 = !DILocation(line: 77, column: 10, scope: !121)
!139 = !DILocation(line: 78, column: 7, scope: !121)
!140 = !DILocation(line: 78, column: 19, scope: !121)
!141 = !DILocation(line: 78, column: 32, scope: !121)
!142 = !DILocation(line: 78, column: 38, scope: !121)
!143 = !DILocation(line: 78, column: 44, scope: !121)
!144 = !DILocation(line: 78, column: 5, scope: !121)
!145 = !DILocation(line: 79, column: 11, scope: !121)
!146 = !DILocation(line: 79, column: 9, scope: !121)
!147 = !DILocation(line: 80, column: 14, scope: !121)
!148 = !DILocation(line: 80, column: 26, scope: !121)
!149 = !DILocation(line: 80, column: 12, scope: !121)
!150 = !DILocation(line: 81, column: 3, scope: !121)
!151 = !DILocation(line: 84, column: 5, scope: !10)
!152 = !DILocation(line: 84, column: 17, scope: !10)
!153 = !DILocation(line: 84, column: 29, scope: !10)
!154 = !DILocation(line: 84, column: 35, scope: !10)
!155 = !DILocation(line: 84, column: 3, scope: !10)
!156 = !DILocation(line: 85, column: 5, scope: !10)
!157 = !DILocation(line: 85, column: 17, scope: !10)
!158 = !DILocation(line: 85, column: 29, scope: !10)
!159 = !DILocation(line: 85, column: 35, scope: !10)
!160 = !DILocation(line: 85, column: 3, scope: !10)
!161 = !DILocation(line: 87, column: 9, scope: !162)
!162 = distinct !DILexicalBlock(scope: !10, file: !1, line: 87, column: 3)
!163 = !DILocation(line: 87, column: 7, scope: !162)
!164 = !DILocation(line: 87, column: 14, scope: !165)
!165 = !DILexicalBlockFile(scope: !166, file: !1, discriminator: 1)
!166 = distinct !DILexicalBlock(scope: !162, file: !1, line: 87, column: 3)
!167 = !DILocation(line: 87, column: 18, scope: !165)
!168 = !DILocation(line: 87, column: 16, scope: !165)
!169 = !DILocation(line: 87, column: 3, scope: !165)
!170 = !DILocation(line: 88, column: 26, scope: !171)
!171 = distinct !DILexicalBlock(scope: !166, file: !1, line: 87, column: 31)
!172 = !DILocation(line: 88, column: 25, scope: !171)
!173 = !DILocation(line: 88, column: 30, scope: !171)
!174 = !DILocation(line: 88, column: 9, scope: !171)
!175 = !DILocation(line: 88, column: 7, scope: !171)
!176 = !DILocation(line: 89, column: 7, scope: !171)
!177 = !DILocation(line: 89, column: 19, scope: !171)
!178 = !DILocation(line: 89, column: 33, scope: !171)
!179 = !DILocation(line: 89, column: 39, scope: !171)
!180 = !DILocation(line: 89, column: 5, scope: !171)
!181 = !DILocation(line: 90, column: 29, scope: !171)
!182 = !DILocation(line: 90, column: 25, scope: !171)
!183 = !DILocation(line: 90, column: 32, scope: !171)
!184 = !DILocation(line: 90, column: 9, scope: !171)
!185 = !DILocation(line: 90, column: 7, scope: !171)
!186 = !DILocation(line: 91, column: 7, scope: !171)
!187 = !DILocation(line: 91, column: 19, scope: !171)
!188 = !DILocation(line: 91, column: 33, scope: !171)
!189 = !DILocation(line: 91, column: 39, scope: !171)
!190 = !DILocation(line: 91, column: 5, scope: !171)
!191 = !DILocation(line: 92, column: 3, scope: !171)
!192 = !DILocation(line: 87, column: 27, scope: !193)
!193 = !DILexicalBlockFile(scope: !166, file: !1, discriminator: 2)
!194 = !DILocation(line: 87, column: 3, scope: !193)
!195 = !DILocation(line: 94, column: 3, scope: !10)
!196 = !DILocation(line: 94, column: 9, scope: !197)
!197 = !DILexicalBlockFile(scope: !198, file: !1, discriminator: 1)
!198 = distinct !DILexicalBlock(scope: !199, file: !1, line: 94, column: 3)
!199 = distinct !DILexicalBlock(scope: !10, file: !1, line: 94, column: 3)
!200 = !DILocation(line: 94, column: 13, scope: !197)
!201 = !DILocation(line: 94, column: 25, scope: !197)
!202 = !DILocation(line: 94, column: 11, scope: !197)
!203 = !DILocation(line: 94, column: 3, scope: !197)
!204 = !DILocation(line: 95, column: 7, scope: !205)
!205 = distinct !DILexicalBlock(scope: !198, file: !1, line: 94, column: 46)
!206 = !DILocation(line: 95, column: 19, scope: !205)
!207 = !DILocation(line: 95, column: 33, scope: !205)
!208 = !DILocation(line: 95, column: 39, scope: !205)
!209 = !DILocation(line: 95, column: 5, scope: !205)
!210 = !DILocation(line: 96, column: 7, scope: !205)
!211 = !DILocation(line: 96, column: 19, scope: !205)
!212 = !DILocation(line: 96, column: 33, scope: !205)
!213 = !DILocation(line: 96, column: 39, scope: !205)
!214 = !DILocation(line: 96, column: 5, scope: !205)
!215 = !DILocation(line: 97, column: 3, scope: !205)
!216 = !DILocation(line: 94, column: 42, scope: !217)
!217 = !DILexicalBlockFile(scope: !198, file: !1, discriminator: 2)
!218 = !DILocation(line: 94, column: 3, scope: !217)
!219 = !DILocation(line: 100, column: 10, scope: !10)
!220 = !DILocation(line: 100, column: 3, scope: !10)
!221 = !DILocation(line: 101, column: 1, scope: !10)
!222 = !DILocalVariable(name: "ctxt", arg: 1, scope: !47, file: !1, line: 103, type: !13)
!223 = !DILocation(line: 103, column: 37, scope: !47)
!224 = !DILocalVariable(name: "data", arg: 2, scope: !47, file: !1, line: 104, type: !34)
!225 = !DILocation(line: 104, column: 43, scope: !47)
!226 = !DILocalVariable(name: "len", arg: 3, scope: !47, file: !1, line: 105, type: !36)
!227 = !DILocation(line: 105, column: 35, scope: !47)
!228 = !DILocation(line: 108, column: 5, scope: !47)
!229 = !DILocation(line: 108, column: 11, scope: !47)
!230 = !DILocation(line: 108, column: 22, scope: !47)
!231 = !DILocation(line: 108, column: 36, scope: !47)
!232 = !DILocation(line: 108, column: 42, scope: !47)
!233 = !DILocation(line: 108, column: 58, scope: !47)
!234 = !DILocation(line: 108, column: 64, scope: !47)
!235 = !DILocation(line: 108, column: 3, scope: !47)
!236 = !DILocation(line: 109, column: 3, scope: !47)
!237 = !DILocalVariable(name: "ctxt", arg: 1, scope: !51, file: !1, line: 113, type: !13)
!238 = !DILocation(line: 113, column: 35, scope: !51)
!239 = !DILocalVariable(name: "result", arg: 2, scope: !51, file: !1, line: 113, type: !7)
!240 = !DILocation(line: 113, column: 56, scope: !51)
!241 = !DILocalVariable(name: "hashparams", scope: !51, file: !1, line: 115, type: !19)
!242 = !DILocation(line: 115, column: 23, scope: !51)
!243 = !DILocation(line: 115, column: 36, scope: !51)
!244 = !DILocation(line: 115, column: 42, scope: !51)
!245 = !DILocation(line: 120, column: 7, scope: !246)
!246 = distinct !DILexicalBlock(scope: !51, file: !1, line: 120, column: 6)
!247 = !DILocation(line: 120, column: 6, scope: !51)
!248 = !DILocation(line: 121, column: 32, scope: !246)
!249 = !DILocation(line: 121, column: 38, scope: !246)
!250 = !DILocation(line: 122, column: 6, scope: !246)
!251 = !DILocation(line: 122, column: 12, scope: !246)
!252 = !DILocation(line: 122, column: 23, scope: !246)
!253 = !DILocation(line: 121, column: 53, scope: !246)
!254 = !DILocation(line: 121, column: 12, scope: !246)
!255 = !DILocation(line: 121, column: 5, scope: !246)
!256 = !DILocation(line: 124, column: 5, scope: !51)
!257 = !DILocation(line: 124, column: 17, scope: !51)
!258 = !DILocation(line: 124, column: 30, scope: !51)
!259 = !DILocation(line: 124, column: 38, scope: !51)
!260 = !DILocation(line: 124, column: 44, scope: !51)
!261 = !DILocation(line: 124, column: 3, scope: !51)
!262 = !DILocation(line: 125, column: 5, scope: !51)
!263 = !DILocation(line: 125, column: 17, scope: !51)
!264 = !DILocation(line: 125, column: 31, scope: !51)
!265 = !DILocation(line: 125, column: 37, scope: !51)
!266 = !DILocation(line: 126, column: 4, scope: !51)
!267 = !DILocation(line: 126, column: 12, scope: !51)
!268 = !DILocation(line: 126, column: 24, scope: !51)
!269 = !DILocation(line: 125, column: 3, scope: !51)
!270 = !DILocation(line: 127, column: 5, scope: !51)
!271 = !DILocation(line: 127, column: 17, scope: !51)
!272 = !DILocation(line: 127, column: 30, scope: !51)
!273 = !DILocation(line: 127, column: 38, scope: !51)
!274 = !DILocation(line: 127, column: 44, scope: !51)
!275 = !DILocation(line: 127, column: 3, scope: !51)
!276 = !DILocation(line: 128, column: 3, scope: !51)
!277 = !DILocation(line: 129, column: 3, scope: !51)
